#pragma once
#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <utility>
#include <vector>
#include <functional>
#include <stack>
#include <memory>
#include "engine/engine.h"
#include "engine/scene.h"
template <typename T>
class ObjectPool {
public:
    explicit ObjectPool(size_t size, std::function<void(std::shared_ptr<Entity>)> initFunc);
    std::shared_ptr<Entity> acquireObject();
    void releaseObject(std::shared_ptr<Entity>& entity);
    void forEach(const std::function<void(std::shared_ptr<Entity>)>& func);

private:
    std::vector<std::shared_ptr<Entity>> pool;
    std::stack<size_t> availableIndices;
    std::function<void(std::shared_ptr<Entity>)> initializer;
};

template <typename T>
ObjectPool<T>::ObjectPool(size_t size, std::function<void(std::shared_ptr<Entity>)> initFunc)
        : initializer(std::move(initFunc)) {
    if (Engine::_activeScene == nullptr) {
        throw std::runtime_error("ObjectPool must be initialized after a scene has been loaded");
    }
    for (size_t i = 0; i < size; ++i) {
        auto entity = Engine::_activeScene->makeEntity();
        entity->setPosition({10000, 10000});
        initializer(entity);
        pool.push_back(entity);
        availableIndices.push(i);
        entity->setVisible(false);
    }
}

template <typename T>
std::shared_ptr<Entity> ObjectPool<T>::acquireObject() {
    if (availableIndices.empty()) {
        return nullptr;
    }
    size_t index = availableIndices.top();
    availableIndices.pop();
    auto entity = pool[index];
    entity->setVisible(true);
    entity->addComponent<T>();
    return entity;
}

template <typename T>
void ObjectPool<T>::releaseObject(std::shared_ptr<Entity>& entity) {
    auto it = std::find(pool.begin(), pool.end(), entity);
    if (it != pool.end()) {
        size_t index = std::distance(pool.begin(), it);
        availableIndices.push(index);
        entity->setVisible(false);
        entity->setPosition({10000, 10000});
        entity->removeComponents();
        std::cout << "Object released" << std::endl;
        std::cout << "Pool size: " << pool.size() << std::endl;
        std::cout << "Available indices: " << availableIndices.size() << std::endl;
    } else {
        throw std::runtime_error("Attempted to release an entity not part of the pool");
    }
}

template <typename T>
void ObjectPool<T>::forEach(const std::function<void(std::shared_ptr<Entity>)>& func) {
    for (auto& entity : pool) {
        if (entity->isVisible()) {
            func(entity);
        }
    }
}

#endif //OBJECT_POOL_H