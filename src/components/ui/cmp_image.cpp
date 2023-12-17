#include "cmp_image.h"
#include "../engine/system_renderer.h"

using namespace sf;

ImageComponent::ImageComponent(Entity* p)
        : Component(p) {}

void ImageComponent::update(double dt) {
    // Update logic for the image, if necessary
}

void ImageComponent::render() {
    Renderer::queue(&_sprite);
}

void ImageComponent::setImage(const sf::Texture& texture) {
    _sprite.setTexture(texture);
    // Set origin, position, or other properties if needed
}

sf::Sprite& ImageComponent::getSprite() {
    return _sprite;
}
