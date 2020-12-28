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
        comm_world.send(0, ORDER_CHANNEL, WRITE);
        comm_world.send(0, ORDER_CHANNEL, key);
        comm_world.send(0, ORDER_CHANNEL, value);
        comm_world.recv(0, ORDER_CHANNEL, result);
        std::cout << "LISTENER " << comm_world.rank() << ": WRITE RESULT " << result << '\n';
    }

    void update(const std::string& key, int newValue) {
        int result;
        std::cout << "LISTENER " << comm_world.rank() << ": UPDATE KEY " << key << " VALUE " << newValue << '\n';
        comm_world.send(0, ORDER_CHANNEL, UPDATE);
        comm_world.send(0, ORDER_CHANNEL, key);
        comm_world.send(0, ORDER_CHANNEL, newValue);
        comm_world.recv(0, ORDER_CHANNEL, result);
        std::cout << "LISTENER " << comm_world.rank() << ": UPDATE RESULT: " << result << '\n';
    }

    void subscribe(const std::string& key) {
        std::cout << "LISTENER " << comm_world.rank() << ": SUBSCRIBE REQUESTED FOR KEY " << key << '\n';
        comm_world.send(0, ORDER_CHANNEL, SUBSCRIBE);
        comm_world.send(0, ORDER_CHANNEL, key);
    }

    void exit() {
        comm_world.send(0, ORDER_CHANNEL, EXIT);
    }

    int operator[] (const std::string& key) {
        valuesMutex.lock();
        int val = values[key];
        valuesMutex.unlock();
        return val;
    }

    explicit DSMListener() {
        this->notificationThread = std::move(std::thread([this] () {
            mpi::communicator other_comm_world;
            std::cout << "LISTENER " << other_comm_world.rank() << ": STARTED TO LISTEN FOR NOTIFICATIONS\n";
            std::string key;
            int value;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
            while (true) {
                other_comm_world.recv(0, NOTIFY_CHANNEL, key);
                other_comm_world.recv(0, NOTIFY_CHANNEL, value);
                std::cout << "NOTIFICATION " <<  other_comm_world.rank() << ": NOTIFICATION RECEIVED " << key << ' ' << value << '\n';
                valuesMutex.lock();
                values[key] = value;
                valuesMutex.unlock();
            }
#pragma clang diagnostic pop
        }));
        sleep(5);
    }

    ~DSMListener() {
        this->notificationThread.join();
    }
};

#endif //LAB8_DSMLISTENER_H