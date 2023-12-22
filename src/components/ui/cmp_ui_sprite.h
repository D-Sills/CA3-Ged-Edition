#pragma once

#include <ecm.h>
#include <SFML/Graphics.hpp>
#include <memory>

class UISpriteComponent : public Component {
protected:
    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<sf::Texture> texture;

public:
    UISpriteComponent() = delete;
    explicit UISpriteComponent(Entity* parent);

    void init(const std::shared_ptr<sf::Texture>& tex, const sf::IntRect& rect = sf::IntRect());
    void update(double dt) override;
    void render() override;
    sf::Sprite& getSprite() const;
    void setTexture(const std::shared_ptr<sf::Texture>& tex);
    void setTextureRect(const sf::IntRect& rect);
    void setPos(sf::Vector2f pos);

};
