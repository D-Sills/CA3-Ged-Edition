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
    std::shared_ptr<Entity> acquireObject();
    void releaseObject(const std::shared_ptr<Entity>& entity);
    void forEach(const std::function<void(std::shared_ptr<Entity>)>& func);
    std::vector<std::shared_ptr<Entity>> getPool() {
        return pool;
    }

private:
    std::vector<std::shared_ptr<Entity>> pool;
    std::vector<bool> available;
};

template <typename T>
ObjectPool<T>::ObjectPool(size_t size) : pool(size), available(size, true) {
    if (Engine::_activeScene == nullptr) {
        throw std::runtime_error("ObjectPool must be initialized after a scene has been loaded");
    }
    for (size_t i = 0; i < size; ++i) {
        auto entity = Engine::_activeScene->makeEntity();
        entity->template addComponent<T>();
        pool[i] = entity;
        pool[i]->setVisible(false);
    }
}

template <typename T>
std::shared_ptr<Entity> ObjectPool<T>::acquireObject() {
    for (size_t i = 0; i < pool.size(); ++i) {
        if (available[i]) {
            available[i] = false;
            pool[i]->setVisible(true);
            return pool[i]; // Returns the Entity with the component attached
        }
    }
    return nullptr; // Pool is full
}


template <typename T>
void ObjectPool<T>::releaseObject(const std::shared_ptr<Entity>& entity) {
    auto it = std::find(pool.begin(), pool.end(), entity);
    if (it != pool.end()) {
        size_t index = std::distance(pool.begin(), it);
        available[index] = true;
        entity->setVisible(false);
        //entity->setForDelete();
    }
}


template <typename T>
void ObjectPool<T>::forEach(const std::function<void(std::shared_ptr<Entity>)>& func) {
    for (auto& entity : pool) {
        if (!available[std::distance(pool.begin(), std::find(pool.begin(), pool.end(), entity))]) {
            func(entity); // Apply the function to the Entity
        }
    }
}

