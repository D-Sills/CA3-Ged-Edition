#include "cmp_pathfinding.h"
#include "../../engine/engine.h"

PathfindingComponent::PathfindingComponent(Entity* p)
        : Component(p), _generator(Engine::generator), _pathRequested(false), _pathComplete(true), _speed(100.0f) {}

void PathfindingComponent::update(double dt) {
    if (_pathRequested && !_path.empty()) {
        followPath(dt);
    }
}

void PathfindingComponent::requestPath(const sf::Vector2f& target) {
    _target = target;
    _pathRequested = true;
    _pathComplete = false;

    //AStar::Vec2i start(_parent->getPosition().x, _parent->getPosition().y);
    //AStar::Vec2i end(target.x, target.y);
    //auto path = _generator.findPath(start, end);

    _path.clear();
    //for (auto& p : path) {
    //    _path.emplace_back(p.x, p.y); // Convert grid points to world positions
    //}
}

bool PathfindingComponent::isPathComplete() const {
    return _pathComplete;
}

void PathfindingComponent::followPath(double dt) {
    if (_path.empty()) {
        _pathComplete = true;
        return;
    }

    // Move towards the next waypoint in the path
    auto& pos = _parent->getPosition();
    auto& nextPos = _path.front();
    sf::Vector2f direction = nextPos - pos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 1.0f) {
        direction /= length;
        _parent->setPosition(pos + direction * _speed * static_cast<float>(dt));
    } else {
        _path.erase(_path.begin());
    }
}

