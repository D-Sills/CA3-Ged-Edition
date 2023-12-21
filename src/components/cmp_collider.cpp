#include "cmp_collider.h"

ColliderComponent::ColliderComponent(Entity* p, const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
        : Component(p) {
      _parent->setOnCollision([this](const std::shared_ptr<Entity>& e) {
        onCollisionEnter(e);
      });
}

void ColliderComponent::onCollisionEnter(const std::shared_ptr<Entity>& e) {
    e->setAlive(false);
}




