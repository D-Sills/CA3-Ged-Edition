#include <functional>
#include "cmp_collider.h"
#include "../engine/system_physics.h"

ColliderComponent::ColliderComponent(Entity* p, const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
        : Component(p) {
      // Set user data to point to the parent entity
}

void ColliderComponent::update(double dt) {
    // Update entity position to match the physics body

}

b2Body* ColliderComponent::getBody() const {
    return _body.get();
}

void ColliderComponent::onCollisionEnter(std::function<void(Entity*)> callback) {
    _onCollisionEnter = callback;

}
