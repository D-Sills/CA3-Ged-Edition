#pragma once
#include "ecm.h"
#include "cmp_pathfinding.h"

enum class ZombieState { Idle, Chasing, Attacking };

class ZombieAIComponent : public Component {
public:
    ZombieAIComponent(Entity* p, float attackRange, float damage);

    void update(double dt) override;
    void render() override {}

    void setTarget(const std::shared_ptr<Entity>& target);

private:
    std::shared_ptr<PathfindingComponent> _pathfindingComponent;
    std::shared_ptr<Entity> _target;
    float _attackRange;
    float _damage;
    ZombieState _currentState;
    sf::Clock _attackTimer;

    void attackTarget();
};

