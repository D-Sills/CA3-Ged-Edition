//
// Created by darrs on 21/12/2023.
//

#include "pickup.h"

#include "../engine/system_resources.h"
#include "../engine/system_physics.h"

Pickup::Pickup(Entity *p, PickupType type) : Component(p) {
    _type = type;
    _sprite = _parent->addComponent<SpriteComponent>();
    switch (_type) {
        case PickupType::HEALTH:
            _sprite->setTexture(Resources::load<Texture>("health.png"));
            break;
        case PickupType::PISTOL_AMMO:
            _sprite->setTexture(Resources::load<Texture>("ammo_pistol.png"));
            break;
        case PickupType::SHOTGUN_AMMO:
            _sprite->setTexture(Resources::load<Texture>("ammo_shotgun.png"));
            break;
        case PickupType::RIFLE_AMMO:
            _sprite->setTexture(Resources::load<Texture>("ammo_rifle.png"));
            break;
    }

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(_parent->getPosition().x / Physics::PIXEL_PER_METER , _parent->getPosition().y / Physics::PIXEL_PER_METER);

    b2CircleShape circleShape;
    circleShape.m_radius = _sprite->getSprite().getTexture()->getSize().x / 2.0f / Physics::PIXEL_PER_METER;

    // Fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.isSensor = true;  // Make it a sensor

   // _body = Physics::GetWorld()->CreateBody(&bodyDef);
   // _body->CreateFixture(&fixtureDef);
    //_body->SetUserData(_parent);

    _parent->setOnCollision([this](Entity* e) { onCollisionEnter(e); });
}

void Pickup::onCollisionEnter(Entity *other) {
    if (other->hasTag("player")) {
        auto p = other->get_components<Player>()[0];
        p->applyPickup(1, _type);
        Physics::markBodyForDestruction(_body);
        _parent->setForDelete();
    }
}