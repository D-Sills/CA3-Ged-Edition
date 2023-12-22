#pragma once

#include "../engine/engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../zombie_factory.h"
#include <LevelSystem.h>

class TestScene : public Scene {
public:
    sf::View gameView;
    sf::View uiView;

    shared_ptr<Entity> player;
    shared_ptr<Entity> hudManager;
    shared_ptr<Entity> crosshair;
    shared_ptr<Entity> pause;
    ZombieSpawner* zombieSpawner;

	void Load() override;

	void Update(const double& dt) override;

	void Render() override;

    void NextWave();

    bool isPaused = false;
};