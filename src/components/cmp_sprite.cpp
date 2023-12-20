#include "cmp_sprite.h"
#include "../engine/system_renderer.h"

using namespace std;
using namespace sf;

SpriteComponent::SpriteComponent(Entity* p) : Component(p) {
    sprite = make_shared<Sprite>();

}

void SpriteComponent::update(double dt) {
    if (sprite == nullptr) {
        return;
    }
    sprite->setPosition(_parent->getPosition());
    sprite->setRotation(_parent->getRotation());
    //std::cout << "rot: " << _parent->getRotation() << std::endl;
}

void SpriteComponent::render() { Renderer::queue(sprite.get()); }

sf::Sprite& SpriteComponent::getSprite() const { return *sprite; }

void SpriteComponent::setTexture(const std::shared_ptr<sf::Texture>& tex) {
    texture = tex;
    sprite->setTexture(*texture);
    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin(bounds.width / 2, bounds.height / 2);
}

void SpriteComponent::setTextureRect(const sf::IntRect& rect) {
    sprite->setTextureRect(rect);
}
