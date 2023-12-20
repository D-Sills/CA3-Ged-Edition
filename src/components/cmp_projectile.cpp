#include "cmp_projectile.h"
#include "../engine/system_renderer.h"
#include "../engine/system_resources.h"
#include "../engine/engine.h"
#include "../engine/scene.h"
#include "cmp_sprite.h"
#include <cmath>

using namespace sf;
using namespace std;

ProjectileComponent::ProjectileComponent(Entity* p)
        : Component(p) {
    _isVisible = false;
    _speed = 1000.0f;
    _damage = 1;
    _angle = 0.0f;
    _sprite = make_shared<Sprite>();
    _sprite->setTexture(*Resources::load<Texture>("bulletGlow.png"));
}

void ProjectileComponent::update(double dt) {
    if (!_isVisible)
        return;

    RenderWindow& window = Engine::GetWindow();
    const View view = window.getView();

    // If bullet is out of bounds. remove/return;
    if (getPosition().x < view.getCenter().x - 100 - view.getSize().x * 0.5 || getPosition().x > view.getCenter().x + 100 + view.getSize().x * 0.5
        || getPosition().y < view.getCenter().y - 100 - view.getSize().y * 0.5 || getPosition().y > view.getCenter().y + 100 + view.getSize().y * 0.5)
    {
        this->_isVisible = false;
        return;
    }
    else {
        float dx = cos(_angle) * _speed * dt;
        float dy = sin(_angle) * _speed * dt;
        move(dx, dy);
    }

    _sprite->setPosition(getPosition());

    // Check for collisions
    auto ecm = Engine::_activeScene->ents.list;
    auto enemies = Engine::_activeScene->ents.find("enemy");
    auto boundingBox = getGlobalBounds();


}

void ProjectileComponent::fire(const sf::Vector2f& pos, float ang) {
    setPosition(pos);
    _angle = ang;
    setRotation(ang);
    _isVisible = true;
}

// Add a method to check visibility
bool ProjectileComponent::isVisible() const {
    return _isVisible;
}

void ProjectileComponent::render() {
    // Render only if visible
    if (_isVisible) {
        Renderer::queue(this);
        Renderer::queue(_sprite.get());
    }
}

void ProjectileComponent::setSpeed(float speed) {
    _speed = speed;
}

void ProjectileComponent::setDamage(int damage) {
    _damage = damage;
}
