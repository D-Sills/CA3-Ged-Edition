#include "cmp_bar.h"
#include "../../engine/system_renderer.h"
#include "cmp_text.h"  // Include text component

using namespace sf;

UIBarComponent::UIBarComponent(Entity* p, const sf::Vector2f& pos,const sf::Vector2f& size, sf::Color fillColor, float maxVal, float currentVal)
        : Component(p), _maxValue(maxVal), _currentValue(currentVal) {

    _barBackground.setSize(size);
    _barBackground.setFillColor(sf::Color::Transparent);
    _barBackground.setOutlineColor(sf::Color::White);
    _barBackground.setOutlineThickness(2.0f);

    _barFill.setSize(size);
    _barFill.setFillColor(fillColor);

    _textComponent = nullptr;

    // Initial bar value setup
    setValue(_currentValue);
    setPosition(pos);
}

void UIBarComponent::update(double dt) {
    // Update the bar's size based on the current value
    float fillWidth = (_currentValue / _maxValue) * _barBackground.getSize().x;
    _barFill.setSize(Vector2f(fillWidth, _barFill.getSize().y));
    updatePosition();
}

void UIBarComponent::render() {
    Renderer::queue(&_barBackground);
    Renderer::queue(&_barFill);
    if (_textComponent) {
        _textComponent->render();
    }
}

void UIBarComponent::setValue(float val) {
    _currentValue = std::max(0.0f, std::min(val, _maxValue));
    if (_textComponent) {
        _textComponent->setText(std::to_string(static_cast<int>(_currentValue)) + "/" + std::to_string(static_cast<int>(_maxValue)));
    }
}

void UIBarComponent::setMaxValue(float maxVal) {
    _maxValue = maxVal;
}

void UIBarComponent::setPosition(const Vector2f& pos) {
    _position = pos;
    updatePosition();
}

void UIBarComponent::attachTextComponent(const std::shared_ptr<TextComponent>& textComponent) {
    _textComponent = textComponent;
    _textComponent->setPosition(_position + Vector2f(_barBackground.getSize().x / 2.0f, -20.0f)); // Adjust as needed
}

void UIBarComponent::updatePosition() {
    _barBackground.setPosition(_position);
    _barFill.setPosition(_position);
    if (_textComponent) {
        _textComponent->setPosition(_position + Vector2f(_barBackground.getSize().x / 2.0f, -20.0f)); // Center text above the bar
    }
}

