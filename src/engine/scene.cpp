#include "scene.h"

void Scene::Update(const double& dt) { ents.update(dt); }

void Scene::Render() { ents.render(); }

EntityManager Scene::getEcm() { return ents; }

bool Scene::isLoaded() const {
    {
        std::lock_guard<std::mutex> lck(_loaded_mtx);
        // Are we already loading asynchronously?
        if (_loaded_future.valid() // yes
            &&                     // Has it finished?
            _loaded_future.wait_for(std::chrono::seconds(0)) ==
            std::future_status::ready) {
            // Yes
            _loaded_future.get();
            _loaded = true;
        }
        return _loaded;
    }
}
void Scene::setLoaded(bool b) {
    {
        std::lock_guard<std::mutex> lck(_loaded_mtx);
        _loaded = b;
    }
}

void Scene::UnLoad() {
    ents.list.clear();
    setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

std::shared_ptr<Entity> Scene::makeEntity() {
    auto e = std::make_shared<Entity>(this);
    ents.list.push_back(e);
    return std::move(e);
}

//void Scene::addEntity(shared_ptr<Entity> entity) {
//	ents.list.push_back(entity);
//}

Scene::~Scene() { UnLoad(); }
