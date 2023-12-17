#pragma once
#include "ecm.h"
#include <SFML/Graphics.hpp>

class ImageComponent : public Component {
public:
    explicit ImageComponent(Entity* p);
    void update(double dt) override;
    void render() override;
    void setImage(const sf::Texture& texture);
    sf::Sprite& getSprite();

private:
    sf::Sprite _sprite;
};
