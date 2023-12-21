#pragma once
#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "ecm.h"
#include "../components/cmp_sprite.h"

#include <SFML/Graphics.hpp>

class Crosshair : public Component {
public:
    Crosshair() = delete;
    explicit Crosshair(Entity* p);
    void update(double dt) override;
    void render() override;

private:
    std::shared_ptr<SpriteComponent> _sprite;
};

#endif
