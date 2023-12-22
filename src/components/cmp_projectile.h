#pragma once
#include "ecm.h"
#include "cmp_sprite.h"
#include "../object_pool.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>

class ProjectileComponent : public Component, public sf::Sprite {
public:
    explicit ProjectileComponent(Entity* p);
    void update(double dt) override;
    void render() override {}

    void fire(const sf::Vector2f& pos, float angle);

    void onCollisionEnter(Entity* other) const;

    void init();

    void setSpeed(float speed);
    void setDamage(int damage);

    int getDamage() const;

    void setOnRelease(const std::function<void()>& onRelease);
    std::function<void()> _onRelease;
    b2Body* _body;
private:

    float _angle{};
    float _speed{};
    int _damage{};

    std::shared_ptr<SpriteComponent> _sprite;

};
