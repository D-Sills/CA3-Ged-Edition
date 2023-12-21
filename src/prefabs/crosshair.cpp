#include "crosshair.h"
#include "../engine/engine.h"
#include "../engine/system_resources.h"


Crosshair::Crosshair(Entity* p) : Component(p) {
    _sprite = _parent->addComponent<SpriteComponent>();
    _sprite->setTexture(Resources::load<sf::Texture>("crosshair.png"));
    _sprite->getSprite().setOrigin(16.f, 16.f);
    _sprite->getSprite().setScale(0.5f, 0.5f);
}

void Crosshair::update(double dt) {
    // set crosshair position to mouse position, convert to world coords
    sf::Vector2 mousePos = sf::Mouse::getPosition(Engine::GetWindow());

    mousePos = static_cast<sf::Vector2i>(Engine::GetWindow().mapPixelToCoords(mousePos));

    _sprite->getSprite().setPosition(mousePos.x, mousePos.y);

    // change crosshair colour based on mouse button pressed, also change texture
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        _sprite->getSprite().setColor(sf::Color::Red);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        _sprite->getSprite().setColor(sf::Color::Green);
    } else {
        _sprite->getSprite().setColor(sf::Color::White);
    }
}

void Crosshair::render() {}

