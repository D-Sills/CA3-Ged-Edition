#include "cmp_character_controller.h"
#include "ecm.h"
#include <LevelSystem.h>

using namespace sf;
using namespace std;

CharacterControllerComponent::CharacterControllerComponent(Entity* p, float speed) : Component(p), _speed(speed), _direction(Direction::Down) { _parent = p; }

void CharacterControllerComponent::move(const sf::Vector2f& p) {
    auto new_pos = _parent->getPosition() + (p * _speed);
    if (validMove(new_pos)) {
        _parent->setPosition(new_pos);
    }
}

void CharacterControllerComponent::move(Direction dir) {
    _direction = dir;
    Vector2f movement;
    switch(dir) {
        case Direction::Up: movement = Vector2f(0, -1); break;
        case Direction::Down: movement = Vector2f(0, 1); break;
        case Direction::Left: movement = Vector2f(-1, 0); break;
        case Direction::Right: movement = Vector2f(1, 0); break;
    }
    move(movement);
}

bool CharacterControllerComponent::validMove(const sf::Vector2f& pos) {
    return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void CharacterControllerComponent::setSpeed(float speed) {
    _speed = speed;
}

float CharacterControllerComponent::getSpeed() const {
    return _speed;
}

Direction CharacterControllerComponent::getDirection() {
    return _direction;
}

void CharacterControllerComponent::setDirection(Direction direction) {
    _direction = direction;
}
