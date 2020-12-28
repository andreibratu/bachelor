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
    std::mutex subscribersMutex;

    std::mutex valuesMutex;

    std::vector<std::thread> threads;

    std::unordered_map<std::string, std::unique_ptr<std::unordered_set<int>>> subscriberList;

    std::unordered_map<std::string, int> values;

    std::unordered_set<int> getSubscribers(const std::string& key) {
        subscribersMutex.lock();
        std::unordered_set<int> answer = *subscriberList[key];
        subscribersMutex.unlock();
        return answer;
    }

    bool write(const std::string& key, int value, int worker, mpi::communicator &comm_world) {
        std::cout << "SUPERVISOR: WRITING KEY " << key << " WITH VALUE " << value << " FOR WORKER " << worker << '\n';
        subscribersMutex.lock();
        valuesMutex.lock();
        if (values.find(key) != values.end()) {
            valuesMutex.unlock();
            subscribersMutex.unlock();
            return false;
        }
        values[key] = value;
        subscriberList[key] = std::make_unique<std::unordered_set<int>>();
        subscriberList[key]->insert(worker);
        std::cout << "WROTE\n";
        std::pair<std::string, int> updateMessage = {key, value};
        comm_world.send(worker, NOTIFY_CHANNEL, updateMessage);
        std::cout << "SENT\n";
        valuesMutex.unlock();
        subscribersMutex.unlock();
        return true;
    }

    void subscribe(const std::string& key, int worker, mpi::communicator &comm_world) {
        std::cout << "SUPERVISOR: SUBSCRIBE FROM " << worker << " ON KEY " << key << '\n';
        subscribersMutex.lock();

        if (subscriberList.find(key) != subscriberList.end()) {
            subscriberList[key]->insert(worker);
            std::pair<std::string, int> updateMessage = {key, values[key]};
            std::cout << "REEEE " << updateMessage.first << " " << updateMessage.second << '\n';
            comm_world.send(worker, NOTIFY_CHANNEL, updateMessage);
            std::cout << "SUPERVISOR: SUBSCRIBE FROM " << worker << " ON KEY " << key << "DONE!!\n";
        }
        std::cout << "WOW\n";
        subscribersMutex.unlock();
    }

    bool update(const std::string& key, int newValue, int worker, mpi::communicator &comm_world) {
        subscribersMutex.lock();
        valuesMutex.lock();
        if(subscriberList[key]->find(worker) == subscriberList[key]->end()) {
            valuesMutex.unlock();
            subscribersMutex.unlock();
            return false;
        }
        values[key] = newValue;
        std::pair<std::string, int> updateMessage = {key, newValue};
        std::unordered_set<int> subs = *subscriberList[key];
        for(auto& sub: subs) {
            comm_world.send(sub, NOTIFY_CHANNEL, updateMessage);
        }
        valuesMutex.unlock();
        subscribersMutex.unlock();
        return true;
    }
public:
    bool finished;

    explicit DSMSupervisor(int numberWorkers) {
        finished = false;
        for(int workerRank = 1; workerRank <= numberWorkers; workerRank++) {
            this->threads.emplace_back(
                    [workerRank, this] () {
                        mpi::communicator comm_world;
                        std::cout << "SUPERVISOR: STARTED THREAD FOR WORKER " << workerRank << '\n';
                        int operation;
                        std::string key;
                        int value;
                        bool result;
                        while (!finished) {
                            comm_world.recv(workerRank, ORDER_CHANNEL, operation);
                            std::cout << "SUPERVISOR: RECEIVED OP REQUEST " << operation << " FROM RANK " << workerRank << '\n';
                            switch (operation) {
                                case WRITE:
                                    comm_world.recv(workerRank, ORDER_CHANNEL, key);
                                    comm_world.recv(workerRank, ORDER_CHANNEL, value);
                                    result = this->write(key, value, workerRank, comm_world);
                                    comm_world.send(workerRank, ORDER_CHANNEL, result ? SUCCESS : FAIL);
                                    break;
                                case SUBSCRIBE:
                                    comm_world.recv(workerRank, ORDER_CHANNEL, key);
                                    this->subscribe(key, workerRank, comm_world);
                                    comm_world.send(workerRank, ORDER_CHANNEL, SUCCESS);
                                    break;
                                case UPDATE:
                                    comm_world.recv(workerRank, ORDER_CHANNEL, key);
                                    comm_world.recv(workerRank, ORDER_CHANNEL, value);
                                    result = this->update(key, value, workerRank, comm_world);
                                    comm_world.send(workerRank, ORDER_CHANNEL, result ? SUCCESS : FAIL);
                                    break;
                                case EXIT:
                                    finished = true;
                                    comm_world.send(workerRank, ORDER_CHANNEL, SUCCESS);
                                    break;
                                default:
                                    comm_world.send(workerRank, ORDER_CHANNEL, FAIL);
                                    break;
                            }
                        }
                    }
            );
        }
        sleep(2);
    }

    ~DSMSupervisor() {
        std::cout << "SUPERVISOR: EXIT\n";
        for (auto &t: threads) t.join();
    }
};


#endif //LAB8_DSMSUPERVISOR_H
