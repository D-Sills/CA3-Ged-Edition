#pragma once
#include "ecm.h"
#include <SFML/Graphics.hpp>

class UIBarComponent : public Component {
public:
    explicit UIBarComponent(Entity* p, const sf::Vector2f& size, sf::Color fillColor, float maxVal = 100.0f, float currentVal = 100.0f);

    void update(double dt) override;
    void render() override;

    void setValue(float val);
    void setMaxValue(float maxVal);

private:
    sf::RectangleShape _barBackground;
    sf::RectangleShape _barFill;
    float _maxValue;
    float _currentValue;
};
