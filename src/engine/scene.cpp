#include "scene.h"
#include "engine.h"

void Scene::Update(const double& dt) {}

void Scene::Render() {}

EntityManager Scene::getEcm() { return ecm; }

EntityManager Scene::getUiEcm() { return ui_ecm; }

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
    ecm.list.clear();
    ui_ecm.list.clear();
    setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

std::shared_ptr<Entity> Scene::makeEntity(const std::string& tag) {
    auto e = std::make_shared<Entity>(this);
    e->addTag(tag);
    std::cout << "makeEntity: " << tag << std::endl;
    ecm.list.push_back(e);
    return std::move(e);
}

std::shared_ptr<Entity> Scene::makeUiEntity(const std::string& tag) {
    auto e = std::make_shared<Entity>(this);
    e->addTag(tag);
    std::cout << "makeUiEntity: " << tag << std::endl;
    ui_ecm.list.push_back(e);
    return std::move(e);
}

Scene::~Scene() { UnLoad(); }
