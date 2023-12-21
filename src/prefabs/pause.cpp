#include "pause.h"
#include "../engine/system_resources.h"
#include "../engine/engine.h"


Pause::Pause(Entity* p) : Component(p) {
    _background = _parent->addComponent<SpriteComponent>();
    _background->setTexture(Resources::load<sf::Texture>("overlay.png"));
    _background->getSprite().setScale(0.5f, 0.5f);
    _background->getSprite().setPosition(Engine::getWindowSize().x / 2, Engine::getWindowSize().y / 2);

    _text = _parent->addComponent<TextComponent>(Engine::getWindowSize().x / 2, Engine::getWindowSize().y / 2, "PAUSED", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");
    _text->setColor(sf::Color::White);
    _text->setTextSize(200);

    _parent->setVisible(false);
}

void Pause::update(double dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        _parent->setVisible(!_parent->isVisible());

        if (_parent->isVisible()) {
            Engine::GetWindow().setMouseCursorVisible(true);
            Engine::_gameState = GameStates::PAUSE;
        } else {
            Engine::GetWindow().setMouseCursorVisible(false);
            Engine::_gameState = GameStates::WAVE;
        }
    }
}

void Pause::render() {

}

