//
// Created by darrs on 21/12/2023.
//

#include "pickup.h"

#include <utility>
#include "../engine/system_resources.h"

Pickup::Pickup(Entity *p, PickupType type) : Component(p) {
    _type = type;
    auto sprite = _parent->addComponent<SpriteComponent>();
    switch (_type) {
        case PickupType::HEALTH:
            sprite->setTexture(Resources::load<Texture>("health.png"));
            break;
        case PickupType::PISTOL_AMMO:
            sprite->setTexture(Resources::load<Texture>("ammo_pistol.png"));
            break;
        case PickupType::SHOTGUN_AMMO:
            sprite->setTexture(Resources::load<Texture>("ammo_shotgun.png"));
            break;
        case PickupType::RIFLE_AMMO:
            sprite->setTexture(Resources::load<Texture>("ammo_rifle.png"));
            break;
    }
}



void Pickup::setOnPickup(std::function<void()> func) {
    onPickup = std::move(func);
}