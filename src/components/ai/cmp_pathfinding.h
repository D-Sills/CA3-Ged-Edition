#pragma once
#include "ecm.h"
#include "AStar.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class PathfindingComponent : public Component {
public:
    PathfindingComponent(Entity* p);

    void update(double dt) override;
    void render() override {}

    void requestPath(const sf::Vector2f& target);
    bool isPathComplete() const;

private:
    AStar::Generator& _generator;
    std::vector<sf::Vector2f> _path;
    sf::Vector2f _target;
    bool _pathRequested;
    bool _pathComplete;
    float _speed; // Movement speed

    void followPath(double dt);
};

