#include "cmp_sprite.h"
#include "../engine/system_renderer.h"

using namespace std;
using namespace sf;

SpriteComponent::SpriteComponent(Entity* p, const shared_ptr<Texture>& tex, const sf::IntRect& rect)
        : Component(p), sprite(make_shared<Sprite>()), texture(tex) {
    sprite->setTexture(*texture);
    if (rect != sf::IntRect()) {
        sprite->setTextureRect(rect);
    }
}

void SpriteComponent::update(double dt) {
    sprite->setPosition(_parent->getPosition());
    sprite->setRotation(deg2rad(_parent->getRotation()));
}

void SpriteComponent::render() { Renderer::queue(sprite.get()); }

sf::Sprite& SpriteComponent::getSprite() const { return *sprite; }

void SpriteComponent::setTexture(const std::shared_ptr<sf::Texture>& tex) {
    texture = tex;
    sprite->setTexture(*texture);
}

void SpriteComponent::setTextureRect(const sf::IntRect& rect) {
    sprite->setTextureRect(rect);
}
