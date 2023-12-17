#pragma once

#include "ecm.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

enum ButtonState { Idle, Hover, Active, Down };

class Button : public Component {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color idleColor, hoverColor, activeColor;
    ButtonState buttonState;
    bool isHoveredFirstTime;

public:
    Button() = delete;
    explicit Button(Entity* parent, const sf::Vector2f& position, const std::string& text,
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor);
    void update(double dt) override;
    void render() override;
    bool isPressed() const;
};
