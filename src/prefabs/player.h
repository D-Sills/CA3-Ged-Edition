#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "../components/cmp_character.h"
#include "../components/cmp_animator.h"
#include "../components/cmp_projectile_emitter.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_character_controller.h"
#include "hud_manager.h"
#include <Box2D/Box2D.h>
#include <ecm.h>

enum class PlayerState {
    IDLE,
    WALKING,
    AIMING,
    RELOADING,
    INTERACTING,
    DEAD
};

enum class UpgradeType {
    HEALTH,
    DAMAGE,
    SPEED
};

enum class WeaponType {
    PISTOL,
    SHOTGUN,
    RIFLE
};

enum class PickupType {
    HEALTH,
    PISTOL_AMMO,
    SHOTGUN_AMMO,
    RIFLE_AMMO,
    XP
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

    std::shared_ptr<HUDManager> _hud;

    int pistolAmmo = 200;
    int shotgunAmmo = 50;
    int rifleAmmo = 100;

    int pistolAmmoMax = 10;
    int shotgunAmmoMax = 4;
    int rifleAmmoMax = 30;

    int currentPistolCount = 10;
    int currentShotgunCount = 4;
    int currentRifleCount = 30;

    bool isReloading = false;
    float reloadTime = 2.0f;
    float reloadTimer = 0.0f;
    float interactCooldown = 0.5f;
    float interactTimer = 0.0f;

    int score = 0;

    float footstepTimer = 0.0f;
    const float footstepInterval = 0.5f;

    float invincibilityTimer = 0.0f;

    float currentXP = 0.0f;

    Animation _idle = Animation(nullptr, {});
    Animation _walk = Animation(nullptr, {});
    Animation _aim = Animation(nullptr, {});
    Animation _reload = Animation(nullptr, {});
    Animation _interact = Animation(nullptr, {});
public:
    explicit Player(Entity* p, const std::shared_ptr<HUDManager>& h);
    ~Player() override {
        _parent->setForDelete();
    }

    void onCollisionEnter(Entity* other) const;

    void reload();
    void interact();
    void startReloading();

    void startAiming();
    void stopAiming();

    void setupAnimations();

    WeaponType currentWeapon;

    void update(double dt) override;
    void render() override;

    void addXP(float amount);

    void applyUpgrade(float amount, UpgradeType type);
    void applyPickup(int amount, PickupType type);
    void switchWeapon(WeaponType type);


    void takeDamage(int damage);
    void die();

    int level = 1;
};

#endif