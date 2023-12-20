#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
	TextComponent() = delete;
	explicit TextComponent(Entity* p, float x, float y, const std::string&  str, const std::string& font);
	void update(double dt) override;

	void render() override;

	~TextComponent() override = default;

	void SetText(const std::string& str);
	void setTextSize(int sizeOfText);

protected:
	std::shared_ptr<sf::Font> _font;
	sf::Text _text;
};
