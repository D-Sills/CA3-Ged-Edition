#include "cmp_ai_chase.h"

ZombieAIComponent::ZombieAIComponent(Entity* p, float attackRange, float damage)
        : Component(p), _attackRange(attackRange), _damage(damage), _currentState(ZombieState::Idle) {
    _pathfindingComponent = _parent->addComponent<PathfindingComponent>(/* Pass AStar::Generator instance */);
}

void ZombieAIComponent::update(double dt) {
    if (_currentState == ZombieState::Chasing && _target) {
        _pathfindingComponent->requestPath(_target->getPosition());
    }

    if (_currentState == ZombieState::Attacking) {
        if (_attackTimer.getElapsedTime().asSeconds() > 1.0f) { // Example attack rate
            attackTarget();
            _attackTimer.restart();
        }
    }

    // Transition to Attacking state
    if (_target && _pathfindingComponent->isPathComplete()) {
        _currentState = ZombieState::Attacking;
    }
}

void ZombieAIComponent::setTarget(const std::shared_ptr<Entity>& target) {
    _target = target;
    _currentState = ZombieState::Chasing;
}

void ZombieAIComponent::attackTarget() {
    // Attack logic, apply damage to the target
    // ...
}

