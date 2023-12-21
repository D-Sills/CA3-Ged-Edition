#include "hud_manager.h"
#include "../engine/engine.h"


HUDManager::HUDManager(Entity* p): Component(p) {
    Engine::GetWindow().setMouseCursorVisible(false);

    // Health Bar - Top Left
    _healthBar = _parent->addComponent<UIBarComponent>(sf::Vector2f(10,10), sf::Vector2f(200, 20), sf::Color::Green);

    // EXP Bar - Below Health Bar
    _expBar = _parent->addComponent<UIBarComponent>(sf::Vector2f(10,40), sf::Vector2f(200, 20), sf::Color::Blue);

    // Timer Text - Middle
    _timerText = _parent->addComponent<TextComponent>(Engine::GetWindow().getSize().x / 2, 50, "00:00", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");
    _timerText->setTextSize(30);

    // Wave Text - Below Timer Text
    _waveText = _parent->addComponent<TextComponent>(Engine::GetWindow().getSize().x / 2, 90, "Wave - 0", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");
    _waveText->setTextSize(30);

    // Score Text - Top Right
    _scoreText = _parent->addComponent<TextComponent>(Engine::GetWindow().getSize().x + 10, 10, "0", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");
    _scoreText->setTextSize(30);

    // Weapon Icon - Bottom Right
    _weaponIcon = _parent->addComponent<SpriteComponent>();
    // Set the weapon icon sprite and position here

    // Ammo Text - Next to Weapon Icon
    _ammoText = _parent->addComponent<TextComponent>(Engine::GetWindow().getSize().x - 50, Engine::GetWindow().getSize().y - 40, "0 | 8", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");
    _ammoText->setTextSize(30);
}

void HUDManager::updateValues(float health, int ammo, int maxAmmo, float time, int score, int wave) {
    // Update HUD elements
    setHealth(health);
    setTimer(time);
    setScore(score);
    setWave(wave);
    setAmmo(ammo, maxAmmo);
}

void HUDManager::setHealth(float health) {
    _healthBar->setValue(health);
}

void HUDManager::setTimer(float time) {
    int minutes = static_cast<int>(time) / 60;
    int seconds = static_cast<int>(time) % 60;
    std::stringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    _timerText->setText(timeStream.str());
}

void HUDManager::setScore(int score) {
    _scoreText->setText(std::to_string(score));
}

void HUDManager::setWave(int wave) {
    _waveText->setText("Wave: " + std::to_string(wave));
}

void HUDManager::setAmmo(int ammo, int maxAmmo) {
    _ammoText->setText(std::to_string(ammo) + " | " + std::to_string(maxAmmo));
}
