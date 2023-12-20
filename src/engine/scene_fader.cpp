#include "scene_fader.h"

FadeManager& FadeManager::getInstance() {
    static FadeManager instance;
    return instance;
}

FadeManager::FadeManager()
        : duration(0), elapsedTime(0), isFading(false), fadeInEffect(true) {
    fadeShape.setSize(sf::Vector2f(1920, 1080)); // Set to your window size
    fadeShape.setFillColor(sf::Color::Black);
}

void FadeManager::fadeIn(float duration) {
    this->duration = duration;
    elapsedTime = 0;
    isFading = true;
    fadeInEffect = true;
    fadeShape.setFillColor(sf::Color(0, 0, 0, 255));
}

void FadeManager::fadeOut(float duration) {
    this->duration = duration;
    elapsedTime = 0;
    isFading = true;
    fadeInEffect = false;
    fadeShape.setFillColor(sf::Color(0, 0, 0, 0));
}

void FadeManager::update(float dt) {
    if (!isFading) return;

    elapsedTime += dt;
    float alpha = fadeInEffect ? (1.0f - (elapsedTime / duration)) * 255.0f
                               : (elapsedTime / duration) * 255.0f;
    alpha = std::max(0.0f, std::min(255.0f, alpha));

    fadeShape.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));

    if (elapsedTime >= duration) {
        isFading = false;
    }
}

void FadeManager::render(sf::RenderWindow& window) {
    if (isFading) {
        window.draw(fadeShape);
    }
}
