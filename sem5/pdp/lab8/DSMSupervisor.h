//
// Created by Andrei Bratu on 20.12.2020.
//

#ifndef LAB8_DSMSUPERVISOR_H
#define LAB8_DSMSUPERVISOR_H

#include <string>
#include "thread"
#include <unordered_map>
#include <unordered_set>
#include <shared_mutex>
#include "DSMValue.h"
#include "DSMOp.h"
#include "DSMOpResult.h"
#include "DSMChannel.h"
#include "DSMOpResult.h"
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

namespace mpi = boost::mpi;

class DSMSupervisor {
private:
    std::mutex opMutex;

    mpi::communicator class_comm_world;

    std::vector<std::thread> threads;

    std::unordered_map<std::string, std::unique_ptr<std::unordered_set<int>>> subscriberList;

    std::unordered_map<std::string, int> values;

    void write(const std::string& key, int value, int worker) {
        opMutex.lock();
        std::cout << "SUPERVISOR: WRITING KEY " << key << " WITH VALUE " << value << " FOR WORKER " << worker << '\n';
        if (values.find(key) != values.end()) {
            class_comm_world.send(worker, ORDER_TAG, FAIL);
            opMutex.unlock();
        }
        values[key] = value;
        subscriberList[key] = std::make_unique<std::unordered_set<int>>();
        subscriberList[key]->insert(worker);
        std::cout << "SUPERVISOR: WORKER " << worker << " IS NOW SUBSCRIBED TO " << key << '\n';
        class_comm_world.send(worker, NOTIFY_TAG, key);
        class_comm_world.send(worker, NOTIFY_TAG, value);
        std::cout << "SUPERVISOR: WORKER " << worker << " WRITE SUCCESS\n";
        class_comm_world.send(worker, ORDER_TAG, SUCCESS);
        opMutex.unlock();
    }

    void subscribe(const std::string& key, int worker) {
        opMutex.lock();
        std::cout << "SUPERVISOR: SUBSCRIBE FROM " << worker << " ON KEY " << key << '\n';

        if (subscriberList.find(key) != subscriberList.end()) {
            assert(subscriberList[key] != nullptr);
            subscriberList[key]->insert(worker);
            class_comm_world.send(worker, NOTIFY_TAG, key);
            class_comm_world.send(worker, NOTIFY_TAG, values[key]);
            std::cout << "SUPERVISOR: SUBSCRIBE FROM " << worker << " ON KEY " << key << " DONE\n";
            class_comm_world.send(worker, ORDER_TAG, SUCCESS);
            opMutex.unlock();
            return;
        }
        class_comm_world.send(worker, ORDER_TAG, FAIL);
        opMutex.unlock();
    }

    void update(const std::string& key, int newValue, int worker) {
        opMutex.lock();
        if(subscriberList[key]->find(worker) == subscriberList[key]->end()) {
            class_comm_world.send(worker, ORDER_TAG, FAIL);
            opMutex.unlock();
            return;
        }
        values[key] = newValue;
        std::unordered_set<int> subscribers = *subscriberList[key];
        for(auto& sub: subscribers) {
            class_comm_world.send(sub, NOTIFY_TAG, key);
            class_comm_world.send(sub, NOTIFY_TAG, newValue);
        }
        class_comm_world.send(worker, ORDER_TAG, SUCCESS);
        opMutex.unlock();
    }
public:
    bool finished;

    explicit DSMSupervisor(int numberWorkers) {
        finished = false;
        for(int workerRank = 1; workerRank <= numberWorkers; workerRank++) {
            this->threads.emplace_back(
                    [workerRank, this] () {
                        std::cout << "SUPERVISOR: STARTED THREAD FOR WORKER " << workerRank << '\n';
                        int operation;
                        std::string key;
                        int value;
                        while (!finished) {
                            class_comm_world.recv(workerRank, ORDER_TAG, operation);
                            std::string op_name;
                            switch(operation) {
                                case 0:
                                    op_name = "WRITE";
                                    break;
                                case 1:
                                    op_name = "SUBSCRIBE";
                                    break;
                                case 2:
                                    op_name = "UPDATE";
                                    break;
                                case 3:
                                    op_name = "EXIT";
                                    break;
                                default:
                                    op_name = "ERR_OP_UNK";
                                    break;
                            }
                            std::cout << "SUPERVISOR: RECEIVED OP REQUEST " << op_name << " FROM RANK " << workerRank << '\n';
                            switch (operation) {
                                case WRITE:
                                    class_comm_world.recv(workerRank, ORDER_TAG, key);
                                    class_comm_world.recv(workerRank, ORDER_TAG, value);
                                    this->write(key, value, workerRank);
                                    break;
                                case SUBSCRIBE:
                                    class_comm_world.recv(workerRank, ORDER_TAG, key);
                                    this->subscribe(key, workerRank);
                                    break;
                                case UPDATE:
                                    class_comm_world.recv(workerRank, ORDER_TAG, key);
                                    class_comm_world.recv(workerRank, ORDER_TAG, value);
                                    this->update(key, value, workerRank);
                                    break;
                                case EXIT:
                                    finished = true;
                                    class_comm_world.send(workerRank, ORDER_TAG, SUCCESS);
                                    break;
                                default:
                                    class_comm_world.send(workerRank, ORDER_TAG, FAIL);
                                    break;
                            }
                        }
                    }
            );
        }
    }

    ~DSMSupervisor() {
        std::cout << "SUPERVISOR: EXIT\n";
        for (auto &t: threads) t.join();
    }
};


#endif //LAB8_DSMSUPERVISOR_H
