#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "engine/engine.h"
#include "engine/scene.h"

template <typename T>
class ObjectPool {
public:
    explicit ObjectPool(size_t size);

    std::shared_ptr<T> acquireObject();
    void releaseObject(std::shared_ptr<T> object);
    void forEach(std::function<void(std::shared_ptr<T>)> func);

private:
    std::vector<std::shared_ptr<T>> pool;
    std::vector<bool> available;
};

template <typename T>
ObjectPool<T>::ObjectPool(size_t size) : pool(size), available(size, true) {
    if (!Engine::_activeScene) {
        throw std::runtime_error("ObjectPool must be initialized after a scene has been loaded");
    }
    for (size_t i = 0; i < size; ++i) {
        pool[i] = Engine::_activeScene->makeEntity();
        pool[i]->template addComponent<T>();
    }
}

template <typename T>
std::shared_ptr<T> ObjectPool<T>::acquireObject() {
    for (size_t i = 0; i < pool.size(); ++i) {
        if (available[i]) {
            available[i] = false;
            return pool[i];
        }
    }
    return nullptr; // Pool is full
}

template <typename T>
void ObjectPool<T>::releaseObject(std::shared_ptr<T> object) {
    auto it = std::find(pool.begin(), pool.end(), object);
    if (it != pool.end()) {
        size_t index = std::distance(pool.begin(), it);
        available[index] = true;
    }
}

template <typename T>
void ObjectPool<T>::forEach(std::function<void(std::shared_ptr<T>)> func) {
    for (auto& object : pool) {
        if (!available[std::distance(pool.begin(), std::find(pool.begin(), pool.end(), object))]) {
            func(object);
        }
    }
}
