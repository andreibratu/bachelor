//
// Created by Andrei Bratu on 20.12.2020.
//

#ifndef LAB8_DSMSUPERVISOR_H
#define LAB8_DSMSUPERVISOR_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <mpl.hpp>
#include <shared_mutex>
#include <DSMValue.h>
#include "DSMOp.h"
#include "DSMOpResult.h"
#include "DSMChannel.h"
#include "DSMOpResult.h"

template <class T>
class DSMSupervisor {
private:
    std::mutex subscribersMutex;

    std::mutex valuesMutex;

    const mpl::communicator &comm_world;

    std::vector<std::thread> threads;

    std::unordered_map<std::string, std::unordered_set<int>*> subscriberList;

    std::unordered_map<std::string, T> values;

    std::unordered_set<int> getSubscribers(const std::string& key) {
        subscribersMutex.lock();
        std::unordered_set<int> answer = *subscriberList[key];
        subscribersMutex.unlock();
        return answer;
    }

    bool write(std::string key, T value, int worker) {
        subscribersMutex.lock();
        valuesMutex.lock();
        if (values.find(value) != values.end()) {
            return false;
        }
        values[key] = value;
        subscriberList[key] = new std::unordered_set<int>(worker);
        std::pair<std::string, T> updateMessage = {key, value};
        comm_world.template send(updateMessage, worker, NOTIFY_CHANNEL);
        valuesMutex.unlock();
        subscribersMutex.unlock();
        return true;
    }

    void subscribe(const std::string& key, int worker) {
        subscribersMutex.lock();
        subscriberList[key]->insert(worker);
        comm_world.template send(values[key], worker, NOTIFY_CHANNEL);
        subscribersMutex.unlock();
    }

    bool update(const std::string& key, T newValue, int worker) {
        subscribersMutex.lock();
        if(subscriberList[key]->find(worker) == subscriberList[key]->end()) {
            return false;
        }
        valuesMutex.lock();
        values[key] = newValue;
        valuesMutex.unlock();
        std::pair<std::string, T> updateMessage = {key, newValue};
        for(auto& sub: *subscriberList[key]) {
            comm_world.template send(updateMessage, sub, NOTIFY_CHANNEL);
        }
        valuesMutex.unlock();
        subscribersMutex.unlock();
    }
public:
    DSMSupervisor(const mpl::communicator &comm, int numberWorkers): comm_world{comm} {
        for(int workerRank = 0; workerRank < numberWorkers; workerRank++) {
            this->threads.emplace_back(
                    [workerRank, this] () {
                        int finished = false;
                        while (!finished) {
                            DSM_OP operation;
                            std::string key;
                            T value;
                            bool result;
                            comm_world.recv(operation, workerRank, ORDER_CHANNEL);
                            switch (operation) {
                                case WRITE:
                                    comm_world.template recv(key, workerRank, ORDER_CHANNEL);
                                    comm_world.template recv(value, workerRank, ORDER_CHANNEL);
                                    result = this->write(key, value, workerRank);
                                    comm_world.template send(result ? SUCCESS : FAIL, workerRank, ORDER_CHANNEL);
                                    break;
                                case SUBSCRIBE:
                                    comm_world.template recv(key, workerRank, ORDER_CHANNEL);
                                    this->subscribe(key, workerRank);
                                    comm_world.template send(SUCCESS, workerRank, ORDER_CHANNEL);
                                    break;
                                case UPDATE:
                                    comm_world.recv(key, workerRank, ORDER_CHANNEL);
                                    comm_world.recv(value, workerRank, ORDER_CHANNEL);
                                    result = this->update(key, value, workerRank);
                                    comm_world.template send(result ? SUCCESS : FAIL, workerRank, ORDER_CHANNEL);
                                    break;
                                case EXIT:
                                    finished = true;
                                    comm_world.template send(SUCCESS, workerRank, ORDER_CHANNEL);
                                    break;
                                default:
                                    comm_world.template send(FAIL, workerRank, ORDER_CHANNEL);
                                    break;
                            }
                        }
                    }
            );
        }
    }

    ~DSMSupervisor() {
        for (auto &t: threads) t.join();
    }
};


#endif //LAB8_DSMSUPERVISOR_H
