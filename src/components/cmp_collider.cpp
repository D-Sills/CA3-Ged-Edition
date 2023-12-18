#include <functional>
#include "cmp_collider.h"
#include "../engine/system_physics.h"

ColliderComponent::ColliderComponent(Entity* p, const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
        : Component(p) {
    _body = std::unique_ptr<b2Body, std::function<void(b2Body*)>>(Physics::GetWorld()->CreateBody(&bodyDef), [](b2Body* b) { Physics::GetWorld()->DestroyBody(b); });
    _body->CreateFixture(&fixtureDef);
    _body->SetUserData(p);  // Set user data to point to the parent entity
}

ColliderComponent::~ColliderComponent() {
    // The unique_ptr with custom deleter will automatically destroy the body
}

void ColliderComponent::update(double dt) {
    // Update entity position to match the physics body
    auto pos = _body->GetPosition();
    _parent->setPosition(pos.x * PIXEL_PER_METER, pos.y * PIXEL_PER_METER); // Assuming PIXEL_PER_METER is defined
}

b2Body* ColliderComponent::getBody() const {
    return _body.get();
}

void ColliderComponent::onCollisionEnter(std::function<void(Entity*)> callback) {
    _onCollisionEnter = callback;

}
