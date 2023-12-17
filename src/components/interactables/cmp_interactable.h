#pragma once
#include "ecm.h"
#include <SFML/Graphics.hpp>
#include <functional>

class InteractableComponent : public Component {
public:
    explicit InteractableComponent(Entity* p);
    void update(double dt) override;
    void render() override;
    virtual void interact(); // To be overridden by derived classes

    sf::FloatRect getBounds() const;
};
