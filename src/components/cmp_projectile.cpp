#include "cmp_projectile.h"
#include "../engine/system_renderer.h"
#include "../engine/system_resources.h"
#include "../engine/engine.h"
#include "../engine/scene.h"
#include "cmp_sprite.h"
#include "../engine/system_physics.h"
#include "cmp_character.h"
#include "cmp_projectile_emitter.h"
#include <cmath>
#include <utility>

using namespace sf;
using namespace std;

ProjectileComponent::ProjectileComponent(Entity* p) : Component(p) {
    _parent->setVisible(false);
    _parent->addTag("bullet");
    _parent->setOnCollision([this](Entity* e) { onCollisionEnter(e); });
    _damage = 1;
    _angle = 0.0f;
    _speed = 100.0f;
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

void ProjectileComponent::update(double dt) {
    if (!_parent->isVisible()) return;

    RenderWindow& window = Engine::GetWindow();
    const View view = window.getView();

    // If bullet is out of bounds. remove/return;
    if (getPosition().x < view.getCenter().x - 100 - view.getSize().x * 0.5 || getPosition().x > view.getCenter().x + 100 + view.getSize().x * 0.5
        || getPosition().y < view.getCenter().y - 100 - view.getSize().y * 0.5 || getPosition().y > view.getCenter().y + 100 + view.getSize().y * 0.5) {
        _parent->setVisible(false);
        return;
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

    // Convert angle to radians
    float radAngle = ang * (b2_pi / 180.f);

    // Adjust position for Box2D world
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

void ProjectileComponent::setOnRelease(const std::function<void()>& onRelease) {
    _onRelease = onRelease;
}

void ProjectileComponent::onCollisionEnter(Entity *other) const {
    if (other->hasTag("enemy")) {
        other->get_components<CharacterComponent>()[0]->setHealth(other->get_components<CharacterComponent>()[0]->getHealth() - _damage);
        if (_onRelease) {
            _onRelease();
        }
    }
}