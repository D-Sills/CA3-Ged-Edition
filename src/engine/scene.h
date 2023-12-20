#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <future>
#include "ecm.h"
#include <SFML/Graphics.hpp>

class Scene {
public:
    Scene() = default;
    virtual ~Scene();
    virtual void Load() = 0;
    virtual void LoadAsync();
    void UnLoad();
    virtual void Update(const double& dt);
    virtual void Render();
    bool isLoaded() const;

    std::shared_ptr<Entity> makeEntity(const std::string& tag = "");
    std::shared_ptr<Entity> makeUiEntity(const std::string& tag = "");

    EntityManager ecm;
    virtual EntityManager getEcm();

    EntityManager ui_ecm;
    virtual EntityManager getUiEcm();
protected:
    void setLoaded(bool);

private:
    mutable bool _loaded{};
    mutable std::future<void> _loaded_future;
    mutable std::mutex _loaded_mtx;
};

#endif