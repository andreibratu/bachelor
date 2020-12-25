//
// Created by Andrei Bratu on 20.12.2020.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#ifndef LAB8_DSMLISTENER_H
#define LAB8_DSMLISTENER_H

#include "DSMOp.h"
#include "DSMChannel.h"
#include <shared_mutex>
#include <mpl.hpp>
#include <unordered_map>

template <class T>
class DSMListener {
private:
    const std::mutex valuesMutex;

    const std::thread notificationThread;

    const mpl::communicator &comm_world;

    std::unordered_map<std::string, T> values;
public:
    void write(const std::string& key, T value) {
        comm_world.template send(WRITE, 0, ORDER_CHANNEL);
        comm_world.template send(key, 0, ORDER_CHANNEL);
        comm_world.template send(value, 0, ORDER_CHANNEL);
    }

    void update(const std::string& key, T newValue) {
        comm_world.template send(UPDATE, 0, ORDER_CHANNEL);
        comm_world.template send(key, 0, ORDER_CHANNEL);
        comm_world.template send(newValue, 0, ORDER_CHANNEL);
    }

    void subscribe(const std::string& key) {
        comm_world.template send(SUBSCRIBE, 0, ORDER_CHANNEL);
        comm_world.template send(key, 0, ORDER_CHANNEL);
    }

    void exit() {
        comm_world.template send(EXIT, 0, ORDER_CHANNEL);
    }

    T operator[] (const std::string& key) {
        valuesMutex.lock();
        T val = values[key];
        valuesMutex.unlock();
        return val;
    }

    explicit DSMListener(const mpl::communicator &comm): comm_world{comm} {
        this->notificationThread = std::thread([this] () {
            std::pair<std::string, T> notification;
            std::cout << "UPDATE IN RANK " << comm_world.rank() << ' ' << notification.first << ' ' << notification.second << '\n';
            while (true) {
                comm_world.template recv(notification, 0, NOTIFY_CHANNEL);
                valuesMutex.lock();
                values[notification.first] = notification.second;
                valuesMutex.unlock();
            }
        });
    }

    ~DSMListener() {
        this->notificationThread.join();
    }
};

#endif //LAB8_DSMLISTENER_H

#pragma clang diagnostic pop