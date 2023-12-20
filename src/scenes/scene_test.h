#pragma once

#include "../engine/engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../player/player.h"
#include "../hud_manager.h"
#include "../zombie_factory.h"

class TestScene : public Scene {
public:
    sf::View gameView;
    sf::View uiView;

    shared_ptr<Entity> player;
    shared_ptr<Entity>  hudManager;
    ZombieSpawner* zombieSpawner;

	void Load() override;

	void Update(const double& dt) override;

	void Render() override;
};