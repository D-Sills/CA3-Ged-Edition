#include "cmp_character.h"

CharacterComponent::CharacterComponent(Entity* p) : Component(p), _health(100), _damage(10), _attackTime(0.0f), _deathTime(0.0f) { _parent = p; }

void CharacterComponent::setHealth(int health) {
    _health = health;
}

void CharacterComponent::setDamage(int damage) {
    _damage = damage;
}

int CharacterComponent::getHealth() const {
    return _health;
}

int CharacterComponent::getDamage() const {
    return _damage;
}


