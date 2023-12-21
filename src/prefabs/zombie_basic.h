#pragma once
#ifndef ZOMBIE_BASIC_H
#define ZOMBIE_BASIC_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../components/cmp_character.h"
#include "../components/ai/cmp_ai_chase.h"
#include "../components/cmp_animator.h"
#include "../components/cmp_collider.h"

class Zombie : public Component{
private:
    std::shared_ptr<sf::Texture> _idle;
    std::shared_ptr<sf::Texture> _attack;

    std::shared_ptr<CharacterComponent> _character;
    std::shared_ptr<ZombieAIComponent> _pathfinding;
    std::shared_ptr<SpriteComponent> _spriteComp;
    std::shared_ptr<ColliderComponent> _collider;
    std::shared_ptr<CharacterControllerComponent> _controller;
public:
    explicit Zombie(Entity* p);

    void init();
    void update(double dt) override;
    void render() override;
};

#endif