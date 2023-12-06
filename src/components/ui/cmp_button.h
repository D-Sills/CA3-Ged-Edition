#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

#include <SFML/Audio.hpp>

enum button_states { BUTTON_IDLE, BUTTON_HOVER, BUTTON_ACTIVED, BUTTON_DOWN };

class Button : public Component {
private:
	sf::RectangleShape shape;
	std::shared_ptr<sf::Font> font;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
    std::shared_ptr<sf::SoundBuffer> sound_buffer;
    sf::Sound soundHover;
    bool isHoveredFirstTime;
    short unsigned buttonState;
    sf::SoundBuffer sound_buffer;
    sf::Text _text;

public:



	sf::Sound soundClick;


	Button() = delete;

	explicit Button(Entity* p, sf::Vector2f position, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	void update(double dt) override;
	void render() override;
	~Button() override = default;

	const bool isPressed() const;

	static button_states _mouseState;
};
