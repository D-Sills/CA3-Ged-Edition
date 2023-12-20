#pragma once

#include "../engine/engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../player/player.h"
#include "../hud_manager.h"
#include "../zombie_factory.h"

class TestScene : public Scene {
public:
	EntityManager* ecm;
    EntityManager* ui_ecm;

    sf::View gameView;
    sf::View uiView;

	sf::Vector2f startingCenter;
	std::string result;

    shared_ptr<Entity> player;
    shared_ptr<Entity>  hudManager;
    ZombieSpawner* zombieSpawner;

	void init();

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

	void render_end() const;
};