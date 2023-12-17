#include "cmp_bar.h"
#include "../../engine/system_renderer.h"

using namespace sf;

UIBarComponent::UIBarComponent(Entity* p, const sf::Vector2f& size, sf::Color fillColor, float maxVal, float currentVal)
        : Component(p), _maxValue(maxVal), _currentValue(currentVal) {

    _barBackground.setSize(size);
    _barBackground.setFillColor(sf::Color::Transparent);
    _barBackground.setOutlineColor(sf::Color::White);
    _barBackground.setOutlineThickness(2.0f);

    _barFill.setSize(size);
    _barFill.setFillColor(fillColor);

    // Initial bar value setup
    setValue(_currentValue);
}

void UIBarComponent::update(double dt) {
    // Update the bar's size based on the current value
    float fillWidth = (_currentValue / _maxValue) * _barBackground.getSize().x;
    _barFill.setSize(Vector2f(fillWidth, _barFill.getSize().y));
    _barFill.setPosition(_parent->getPosition());
    _barBackground.setPosition(_parent->getPosition());
}

void UIBarComponent::render() {
    Renderer::queue(&_barBackground);
    Renderer::queue(&_barFill);
}

void UIBarComponent::setValue(float val) {
    _currentValue = std::max(0.0f, std::min(val, _maxValue));
}

void UIBarComponent::setMaxValue(float maxVal) {
    _maxValue = maxVal;
}
