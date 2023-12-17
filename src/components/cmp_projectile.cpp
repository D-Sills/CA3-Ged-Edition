#include "cmp_projectile.h"
#include "../engine/system_renderer.h"
#include "../engine/system_resources.h"
#include "../engine/engine.h"
#include "../engine/scene.h"
#include "cmp_sprite.h"
#include <cmath>

using namespace sf;
using namespace std;

ProjectileComponent::ProjectileComponent(Entity* p, const sf::Texture& texture, float angle, float speed, int damage)
        : Component(p), _angle(angle), _speed(speed), _damage(damage), _isVisible(true) {
    setTexture(texture);
    setRotation(angle);
    _hitSoundBuffer = *Resources::get<SoundBuffer>("Hit.wav");
    _hitSound.setBuffer(_hitSoundBuffer);
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

    auto ecm = Engine::_activeScene->ents.list;
    auto enemies = Engine::_activeScene->ents.find("enemy");
    auto boundingBox = getGlobalBounds();

    for (const auto& enemy : enemies)
    {
        auto sprite = enemy->GetCompatibleComponent<SpriteComponent>()[0]->getSprite();
        auto spriteBounds = sprite.getGlobalBounds();
        spriteBounds.top += 40;
        spriteBounds.left += 40;
        spriteBounds.width -= 70;
        spriteBounds.height -= 70;
        if (enemy->isAlive() && spriteBounds.intersects(boundingBox))
        {
            // Hide the bullet
            _isVisible = false;
            setPosition(-100, -100);

            // Hit Sound
            soundHit_buffer = Resources::get<SoundBuffer>("Hit.wav");
            soundHit = make_shared<Sound>(*soundHit_buffer);
            soundHit->setVolume(volume);
            soundHit->play();

            auto currentHealth = enemy->GetCompatibleComponent<MonsterComponent>()[0]->get_health();
            enemy->GetCompatibleComponent<MonsterComponent>()[0]->set_health(currentHealth - _damage);
        }
    }
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
    }
}

void ProjectileComponent::setSpeed(float speed) {
    _speed = speed;
}

void ProjectileComponent::setDamage(int damage) {
    _damage = damage;
}
