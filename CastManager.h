/* Ragekill3377's CastManager*/
/* Honestly, it's useless. It just... looks satisfying.*/

/*

auto castManager = CastManager::init(); // shared ptr
castManager->cast_const
castManager->cast_static
castManager->dynamic
castManager->reinterpret

*/
#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include <functional>
#include <thread>
#include <chrono>
#include <pthread.h>

class CastManager {
public:
    static std::shared_ptr<CastManager> init();
    template <typename From, typename To>
    void cast_static(std::shared_ptr<void> ptr);
    template <typename From, typename To>
    void dynamic(std::shared_ptr<From> ptr);
    template <typename From, typename To>
    void reinterpret(std::shared_ptr<void> ptr);

private:
    template <typename From, typename To>
    void log_cast_error(const char* type);

    template <typename From, typename To>
    void log_reinterpret();

    void enqueue_cast_task(std::function<void()> task);
};

std::shared_ptr<CastManager> CastManager::init() {
    return std::make_shared<CastManager>();
}

template <typename From, typename To>
void CastManager::cast_static(std::shared_ptr<void> ptr) {
    std::function<void()> task = [this, ptr]() {
        To* result = nullptr;
        if (ptr && std::is_convertible<From*, To*>::value) {
            result = std::static_pointer_cast<To>(ptr).get();
        } else {
            log_cast_error<From, To>("static");
        }
    };
    enqueue_cast_task(task);
}

template <typename From, typename To>
void CastManager::dynamic(std::shared_ptr<From> ptr) {
    std::function<void()> task = [this, ptr]() {
        if (ptr) {
            auto result = std::dynamic_pointer_cast<To>(ptr);
            if (result) {
                std::cout << "Dynamic cast succeeded!" << std::endl;
            } else {
                log_cast_error<From, To>("dynamic");
            }
        }
    };
    enqueue_cast_task(task);
}


template <typename From, typename To>
void CastManager::reinterpret(std::shared_ptr<void> ptr) {
    std::function<void()> task = [this, ptr]() {
        To* result = nullptr;
        if (ptr) {
            result = reinterpret_cast<To*>(ptr.get());
            log_reinterpret<From, To>();
        }
    };
    enqueue_cast_task(task);
}

template <typename From, typename To>
void CastManager::log_cast_error(const char* type) {
    std::cerr << "Cast error: " << typeid(From).name() << " to " << typeid(To).name() << " (" << type << ")" << std::endl;
}

template <typename From, typename To>
void CastManager::log_reinterpret() {
    std::string msg = "Reinterpreted " + std::string(typeid(From).name()) + " to " + typeid(To).name();
    std::cerr << msg << std::endl;
}

void CastManager::enqueue_cast_task(std::function<void()> task) {
    pthread_t thread;
    pthread_create(&thread, nullptr, [](void* arg) -> void* {
        auto taskFunc = static_cast<std::function<void()>*>(arg);
        (*taskFunc)();
        return nullptr;
    }, new std::function<void()>(task));
    pthread_detach(thread);
}
