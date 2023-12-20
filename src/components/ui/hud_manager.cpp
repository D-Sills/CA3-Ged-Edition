#include "hud_manager.h"
#include "../../engine/scene.h"
#include "../../engine/system_resources.h"
#include "../../engine/engine.h"

HUDManager::HUDManager(Entity* p): Component(p) {
    // Initialize HUD elements
    Engine::GetWindow().setMouseCursorVisible(false);

    _healthBar = _parent->addComponent<UIBarComponent>(sf::Vector2f(10,10) ,sf::Vector2f(500, 50), sf::Color::Green);

    _crosshair = _parent->addComponent<SpriteComponent>();
    _crosshair->setTexture(Resources::load<sf::Texture>("crosshair.png"));

    _timerText = _parent->addComponent<TextComponent>(400, 220, "00:00", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");
    _timerText->setTextSize(30);

    _scoreText = _parent->addComponent<TextComponent>(500, 300, "Score: 0", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");
    _scoreText->setTextSize(30);
}

void HUDManager::update(double dt) {


    // set crosshair position to mouse position, convert to world coords
    sf::Vector2 mousePos = sf::Mouse::getPosition(Engine::GetWindow());

    mousePos = static_cast<sf::Vector2i>(Engine::GetWindow().mapPixelToCoords(mousePos));

    _crosshair->getSprite().setPosition(mousePos.x, mousePos.y);
}

void HUDManager::render() {
    // Render all HUD elements

}

void HUDManager::setHealth(float health) {
    _healthBar->setValue(health);
}

void HUDManager::setTimer(float time) {
    int minutes = time / 60;
    int seconds = time - (minutes * 60);
    std::string timeString = std::to_string(minutes) + ":" + std::to_string(seconds);
    _timerText->setText(timeString);
}

void HUDManager::setScore(int score) {
    _scoreText->setText("Score: " + std::to_string(score));
}
