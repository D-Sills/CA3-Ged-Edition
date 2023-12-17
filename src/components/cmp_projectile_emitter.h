#pragma once
#include "ecm.h"
#include "cmp_projectile.h"
#include <SFML/Audio.hpp>
#include <vector>

class ProjectileEmitterComponent : public Component {
public:
    explicit ProjectileEmitterComponent(Entity* parent, int poolSize, float fireRate);
    void update(double dt) override;
    void render() override;
    void fireProjectile(const sf::Vector2f& position, float angle);
    void setFireRate(float fireRate);
    void setProjectileSpeed(float speed);
    void setProjectileDamage(int damage);

private:
    std::vector<std::shared_ptr<ProjectileComponent>> _projectiles;
    int _poolSize;
    float _fireRate;
    float _timeSinceLastFire;
    sf::Sound _fireSound;
    sf::SoundBuffer _fireSoundBuffer;
};

