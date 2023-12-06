#pragma once

#include "../engine/scene.h"
#include "../engine/engine.h"
#include "../components/ui/cmp_button.h"
#include "SFML/Graphics/Sprite.hpp"

class MenuScene : public Scene {
public:
	MenuScene() = default;
	~MenuScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

	sf::View menuView;

	std::shared_ptr<Entity> btnExit;
	std::shared_ptr<Entity> btnSetting;
	std::shared_ptr<Entity> btnStart;

	sf::Sprite background;

	sf::Music music;
	sf::Texture texture;
	void Render() override;
};
