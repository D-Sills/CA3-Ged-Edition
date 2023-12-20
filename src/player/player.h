#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "../components/cmp_character.h"
#include "../components/cmp_animator.h"
#include "../components/cmp_projectile_emitter.h"
#include "../components/cmp_collider.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_character_controller.h"
#include <ecm.h>

class Player : public Component {
private:
    std::shared_ptr<CharacterComponent> _character;
    std::shared_ptr<CharacterControllerComponent> _controller;
    std::shared_ptr<SpriteComponent> _spriteComp;
    std::shared_ptr<ProjectileEmitterComponent> _projectileEmitter;
    std::shared_ptr<ColliderComponent> _collider;

    int bulletCount = 0;
    int bulletMax = 10;
    int currentBullet = 0;
public:
    explicit Player(Entity* p);

    void update(double dt) override;
    void render() override;
};

#endif