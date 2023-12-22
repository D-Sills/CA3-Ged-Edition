#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "cmp_character_controller.h"
#include "cmp_sprite.h"

using namespace std;
using namespace sf;

class CharacterComponent : public Component {
protected:
    int _health;
    int _damage;
    float _speed;
    float _attackTime;
    float _deathTime;

public:
    explicit CharacterComponent(Entity* p);
    ~CharacterComponent() override = default;

    void setHealth(int health);
    void setDamage(int damage);
    void setSpeed(float speed);
    int getHealth() const;
    int getDamage() const;
    float getSpeed() const;

    void update(double dt) override {}

    void render() override {}
};

#endif