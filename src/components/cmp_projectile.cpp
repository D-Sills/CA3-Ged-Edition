#include "cmp_projectile.h"
#include "../engine/system_renderer.h"
#include "../engine/system_resources.h"
#include "cmp_sprite.h"
#include "../engine/system_physics.h"
#include "cmp_character.h"
#include "../prefabs/zombie_basic.h"
#include <cmath>

using namespace sf;
using namespace std;

ProjectileComponent::ProjectileComponent(Entity* p) : Component(p) {
    _sprite = _parent->addComponent<SpriteComponent>();
    _sprite->setTexture(Resources::load<Texture>("bulletGlow.png"));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;  // Treat this body as a fast moving bullet
    bodyDef.position.Set(_parent->getPosition().x / Physics::PIXEL_PER_METER , _parent->getPosition().y / Physics::PIXEL_PER_METER);

    b2CircleShape circleShape;
    circleShape.m_radius = _sprite->getSprite().getTexture()->getSize().x / 2.0f / Physics::PIXEL_PER_METER;

    // Fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.isSensor = true;  // Make it a sensor

    _body = Physics::GetWorld()->CreateBody(&bodyDef);
    _body->CreateFixture(&fixtureDef);
    _body->SetUserData(_parent);

}

void ProjectileComponent::init() {
    _parent->addTag("bullet");
    _parent->setVisible(true);

    _parent->setOnCollision([this](Entity* e) { onCollisionEnter(e); });
}

void ProjectileComponent::update(double dt) {
    if (!_parent->isVisible()) return;

    RenderWindow& window = Engine::GetWindow();
    const View view = window.getView();

    if (_parent->getPosition().x < view.getCenter().x - 100 - view.getSize().x * 0.5 || _parent->getPosition().x > view.getCenter().x + 100 + view.getSize().x * 0.5
        || _parent->getPosition().y < view.getCenter().y - 100 - view.getSize().y * 0.5 || _parent->getPosition().y > view.getCenter().y + 100 + view.getSize().y * 0.5) {
        if (_onRelease) {
            Physics::markBodyForDestruction(_body);
            _onRelease();
        }
    } else {
        float dx = cos(_angle) * _speed;
        float dy = sin(_angle) * _speed;
        _body->SetLinearVelocity(b2Vec2(dx, dy));

        _parent->setPosition(Vector2f(_body->GetPosition().x * Physics::PIXEL_PER_METER, _body->GetPosition().y * Physics::PIXEL_PER_METER));
    }
}

void ProjectileComponent::fire(const sf::Vector2f& pos, float ang) {
    _parent->setPosition(pos);
    _angle = ang;

    float radAngle = ang * (b2_pi / 180.f);

    b2Vec2 bodyPos(pos.x / Physics::PIXEL_PER_METER, pos.y / Physics::PIXEL_PER_METER);
    _body->SetTransform(bodyPos, radAngle);

    _parent->setVisible(true);
}

void ProjectileComponent::setSpeed(float speed) {
    _speed = speed;
}

void ProjectileComponent::setDamage(int damage) {
    _damage = damage;
}

int ProjectileComponent::getDamage() const {
    return _damage;
}

void ProjectileComponent::setOnRelease(const std::function<void()>& onRelease) {
    _onRelease = onRelease;
}

void ProjectileComponent::onCollisionEnter(Entity *other) const {
    if (!_parent->isVisible()) return;
    if (other->hasTag("enemy")) {
        auto z = other->get_components<Zombie>()[0];
        if (z) {
            z->takeDamage(_damage);
        }

        if (_onRelease) {
            Physics::markBodyForDestruction(_body);
            _onRelease();
        }
    }

}