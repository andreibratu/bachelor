//
// Created by Andrei Bratu on 20.12.2020.
//

#ifndef LAB8_DSMLISTENER_H
#define LAB8_DSMLISTENER_H

#include "DSMOp.h"
#include "DSMChannel.h"
#include <shared_mutex>
#include <unordered_map>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <thread>

namespace mpi = boost::mpi;

class DSMListener {
private:
    std::mutex valuesMutex;

    std::thread notificationThread;

    mpi::communicator comm_world;

    std::unordered_map<std::string, int> values;
public:
    void write(const std::string& key, int value) {
        int result;
        std::cout << "LISTENER " << comm_world.rank() << ": WRITE KEY " << key << " VALUE " << value << '\n';
        comm_world.send(0, ORDER_TAG, WRITE);
        comm_world.send(0, ORDER_TAG, key);
        comm_world.send(0, ORDER_TAG, value);
        comm_world.recv(0, ORDER_TAG, result);
        std::cout << "LISTENER " << comm_world.rank() << ": WRITE RESULT: " << result << '\n';
    }

    void update(const std::string& key, int newValue) {
        int result;
        std::cout << "LISTENER " << comm_world.rank() << ": UPDATE KEY " << key << " VALUE " << newValue << '\n';
        comm_world.send(0, ORDER_TAG, UPDATE);
        comm_world.send(0, ORDER_TAG, key);
        comm_world.send(0, ORDER_TAG, newValue);
        comm_world.recv(0, ORDER_TAG, result);
        std::cout << "LISTENER " << comm_world.rank() << ": UPDATE RESULT: " << result << '\n';
    }

    void subscribe(const std::string& key) {
        std::cout << "LISTENER " << comm_world.rank() << ": SUBSCRIBE REQUESTED FOR KEY " << key << '\n';
        int result;
        comm_world.send(0, ORDER_TAG, SUBSCRIBE);
        comm_world.send(0, ORDER_TAG, key);
        comm_world.recv(0, ORDER_TAG, result);
        std::cout << "LISTENER " << comm_world.rank() << ": SUBSCRIBE RESULT: " << result << '\n';
    }

    void exit() {
        comm_world.send(0, ORDER_TAG, EXIT);
    }

    explicit DSMListener() {
        this->notificationThread = std::move(std::thread([this] () {
            std::cout << "LISTENER " << comm_world.rank() << ": STARTED SECONDARY THREAD TO LISTEN FOR NOTIFICATIONS\n";
            std::string key;
            int value;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
            while (true) {
                comm_world.recv(0, NOTIFY_TAG, key);
                comm_world.recv(0, NOTIFY_TAG, value);
                std::cout << "NOTIFICATION " <<  comm_world.rank() << ": NOTIFICATION RECEIVED " << key << ' ' << value << '\n';
                valuesMutex.lock();
                values[key] = value;
                valuesMutex.unlock();
            }
#pragma clang diagnostic pop
        }));
    }

    ~DSMListener() {
        this->notificationThread.join();
    }
};

#endif //LAB8_DSMLISTENER_H