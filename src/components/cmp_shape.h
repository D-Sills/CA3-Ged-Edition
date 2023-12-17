#pragma once
#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <memory>

class ShapeComponent : public Component {
protected:
    std::shared_ptr<sf::Shape> shape;

public:
    ShapeComponent() = delete;
    explicit ShapeComponent(Entity* parent, const sf::Color& color = sf::Color::White);

    void update(double dt) override;
    void render() override;
    sf::Shape& getShape() const;
    template <typename T, typename... Targs> void setShape(Targs... params);
};



