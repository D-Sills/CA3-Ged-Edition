#include "cmp_character.h"

cmp_character::cmp_character(Entity *p) {
    _parent = p;
    _health = 100;
    _damage = 10;
    _speed = 100.0f;
    _attackTime = 0.0f;
    _deathTime = 0.0f;
    _texture = make_shared<Texture>();
    _texture->loadFromFile("res/img/character.png");
    _sprite = _parent->addComponent<SpriteComponent>();
    _movement = _parent->addComponent<ActorMovementComponent>();
}

void cmp_character::set_health(int health) {
    _health = health;
}

int cmp_character::get_health() const {
    return _health;
}

void cmp_character::set_damage(int damage) {
    _damage = damage;
}

float cmp_character::get_speed() const {
    return _speed;
}

void cmp_character::set_speed(float speed) {
    _speed = speed;
}
