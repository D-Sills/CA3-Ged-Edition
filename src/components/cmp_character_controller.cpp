#include "cmp_character_controller.h"
#include "ecm.h"
#include "../engine/system_physics.h"

using namespace sf;
using namespace std;

CharacterControllerComponent::CharacterControllerComponent(Entity* p, b2Body *body) : Component(p), _direction(Direction::Down), _body(body) {}

void CharacterControllerComponent::move(const sf::Vector2f& p) {
    _moveDirection += b2Vec2(p.x, p.y);
}

void CharacterControllerComponent::update(double dt) {
    if (_moveDirection.LengthSquared() > 0) {
        // Normalize if diagonal movement to prevent faster speed
        _moveDirection.Normalize();
        auto vel = b2Vec2(_moveDirection.x * _speed, _moveDirection.y * _speed);
        _body->SetLinearVelocity(vel);
        // Reset the move direction after applying the velocity
        _moveDirection = b2Vec2(0, 0);
    } else {
        // Stop movement when there is no move command
        _body->SetLinearVelocity(b2Vec2(0, 0));
    }

    _parent->setPosition(Vector2f(_body->GetPosition().x * Physics::PIXEL_PER_METER, _body->GetPosition().y * Physics::PIXEL_PER_METER));
}

void CharacterControllerComponent::setSpeed(float speed) {
    _speed = speed;
}
