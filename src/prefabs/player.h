#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "../components/cmp_character.h"
#include "../components/cmp_animator.h"
#include "../components/cmp_projectile_emitter.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_character_controller.h"
#include <Box2D/Box2D.h>
#include <ecm.h>

enum class PlayerState {
    IDLE,
    WALKING,
    AIMING,
    RELOADING,
    INTERACTING
};

class Player : public Component {
private:
    PlayerState _currentState = PlayerState::IDLE;

    std::shared_ptr<CharacterComponent> _character;
    std::shared_ptr<CharacterControllerComponent> _controller;
    std::shared_ptr<SpriteComponent> _spriteComp;
    std::shared_ptr<ProjectileEmitterComponent> _projectileEmitter;
    std::shared_ptr<AnimatorComponent> _animator;
    b2Body* _body;

    int bulletCount = 0;
    int bulletMax = 10;
    int currentBullet = 0;

    bool isReloading = false;
    float reloadTime = 2.0f;
    float reloadTimer = 0.0f;
    float interactCooldown = 0.5f;
    float interactTimer = 0.0f;

    Animation _idle = Animation(nullptr, {});
    Animation _walk = Animation(nullptr, {});
    Animation _aim = Animation(nullptr, {});
    Animation _reload = Animation(nullptr, {});
    Animation _interact = Animation(nullptr, {});
public:
    explicit Player(Entity* p);

    void onCollisionEnter(Entity* other) const;

    void reload();
    void interact();
    void startReloading();

    void startAiming();
    void stopAiming();

    void setupAnimations();

    void setState(PlayerState state);

    void update(double dt) override;
    void render() override;
};

#endif