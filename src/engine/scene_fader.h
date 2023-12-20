#pragma once
#include <SFML/Graphics.hpp>

class FadeManager {
public:
    static FadeManager& getInstance();

    void fadeIn(float duration);
    void fadeOut(float duration);
    void update(float dt);
    void render(sf::RenderWindow& window);

private:
    FadeManager();
    sf::RectangleShape fadeShape;
    float duration;
    float elapsedTime;
    bool isFading;
    bool fadeInEffect;

    // Disallow copy constructor and assignment operator
    FadeManager(const FadeManager&) = delete;
    FadeManager& operator=(const FadeManager&) = delete;
};

