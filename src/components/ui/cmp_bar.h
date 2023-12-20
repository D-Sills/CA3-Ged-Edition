#pragma once
#include "ecm.h"
#include "cmp_text.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <memory> // For std::shared_ptr

class UIBarComponent : public Component {
public:
    explicit UIBarComponent(Entity* p, const sf::Vector2f& pos ,const sf::Vector2f& size, sf::Color fillColor, float maxVal = 100.0f, float currentVal = 100.0f);

    void update(double dt) override;
    void render() override;

    void setValue(float val);
    void setMaxValue(float maxVal);
    void setPosition(const sf::Vector2f& pos); // New method for setting position
    void attachTextComponent(const std::shared_ptr<TextComponent>& textComponent); // New method for attaching a text component

private:
    sf::RectangleShape _barBackground;
    sf::RectangleShape _barFill;
    float _maxValue;
    float _currentValue;
    sf::Vector2f _position; // Position of the bar
    std::shared_ptr<TextComponent> _textComponent; // Optional text component

    void updatePosition(); // New method for updating the position of the bar and text
};

