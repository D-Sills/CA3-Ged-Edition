#include "cmp_text.h"

#include <utility>
#include "../../engine/system_renderer.h"
#include "../../engine/system_resources.h"

void TextComponent::update(double dt) {}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, float x, float y, const std::string&  str, const std::string& font)
	: Component(p) {
	_text.setString(str);

	_font = Resources::load<sf::Font>(font);
	_text.setFont(*_font);
	_text.setCharacterSize(16);
    _text.setFillColor(sf::Color::White);
	_text.setPosition(sf::Vector2f(x, y));
	_text.setOrigin(_text.getLocalBounds().left + _text.getLocalBounds().width / 2.0f,
		_text.getLocalBounds().top + _text.getLocalBounds().height / 2.0f);
}

void TextComponent::setText(const std::string& str) {
	_text.setString(str);
}

void TextComponent::setTextSize(int size) {
	_text.setCharacterSize(size);
	_text.setOrigin(_text.getLocalBounds().left + _text.getLocalBounds().width / 2.0f,
		_text.getLocalBounds().top + _text.getLocalBounds().height / 2.0f);
}

void TextComponent::setColor(sf::Color color) {
    _text.setFillColor(color);
}

void TextComponent::setPosition(sf::Vector2f pos){
    _text.setPosition(pos);
}