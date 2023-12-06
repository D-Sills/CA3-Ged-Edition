#include <memory>
#include <future>
#include "ecm.h"

class Scene {
public:
    Scene() = default;
    virtual ~Scene();
    virtual void Load() = 0;
    virtual void LoadAsync();
    virtual void UnLoad();
    virtual void Update(const double& dt);
    virtual void Render();
    bool isLoaded() const;

    std::shared_ptr<Entity> makeEntity();
    void addEntity(std::shared_ptr<Entity> entity);

    EntityManager ents;
    virtual EntityManager getEcm();

protected:
    void setLoaded(bool);
private:
    mutable bool _loaded{};
    mutable std::future<void> _loaded_future;
    mutable std::mutex _loaded_mtx;
};
