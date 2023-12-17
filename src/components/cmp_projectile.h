#pragma once
#include "ecm.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>

class ProjectileComponent : public Component, public sf::Sprite {
public:
    explicit ProjectileComponent(Entity* p, const sf::Texture& texture, float angle, float speed, int damage);
    void update(double dt) override;
    void render() override;

    bool isVisible() const;
    void fire(const sf::Vector2f& pos, float angle);

    void setSpeed(float speed);
    void setDamage(int damage);
private:
    float _angle;
    float _speed;
    int _damage;
    bool _isVisible;
    sf::Sound _hitSound;
    sf::SoundBuffer _hitSoundBuffer;
};
