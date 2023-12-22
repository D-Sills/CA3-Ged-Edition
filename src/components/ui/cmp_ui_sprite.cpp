#include "cmp_ui_sprite.h"
#include "../../engine/system_renderer.h"


using namespace std;
using namespace sf;

UISpriteComponent::UISpriteComponent(Entity* p) : Component(p) {
    sprite = make_shared<Sprite>();

}

void UISpriteComponent::update(double dt) {


}

void UISpriteComponent::render() { Renderer::queue(sprite.get()); }

sf::Sprite& UISpriteComponent::getSprite() const { return *sprite; }

void UISpriteComponent::setTexture(const std::shared_ptr<sf::Texture>& tex) {
    texture = tex;
    sprite->setTexture(*texture);
    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin(bounds.width / 2, bounds.height / 2);
}

void UISpriteComponent::setTextureRect(const sf::IntRect& rect) {
    sprite->setTextureRect(rect);
}

void UISpriteComponent::setPos(sf::Vector2f pos) {
    sprite->setPosition(pos);
}