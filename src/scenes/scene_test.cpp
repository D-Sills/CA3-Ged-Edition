#include "../last_light.h"
#include "../components/cmp_character_controller.h"

#include "../components/cmp_sprite.h"
#include <LevelSystem.h>
#include "../engine/system_resources.h"
#include "../player/player.h"
#include "scene_test.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

void TestScene::init() {
	ecm = new EntityManager();
    ui_ecm = new EntityManager();

	// Level global variables
	result = "Not Set";

    // View variables
}

void TestScene::Load() {
	init();
	*ecm = Scene::getEcm();
    *ui_ecm = Scene::getUiEcm();

	//ls::loadLevelFile("res/levels/floorMap.txt");

	int xCount = 25;
	int yCount =25;

    // Player Variables
    gameView = Engine::GetWindow().getDefaultView();
    gameView.reset(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
    Engine::setView(gameView);
    player = makeEntity();
    auto p = player->addComponent<Player>();
    player->setPosition({static_cast<float>(Engine::GetWindow().getSize().x / 2), static_cast<float>(Engine::GetWindow().getSize().y / 2)});

    //HUD Variables
    uiView = Engine::GetWindow().getDefaultView();
    uiView.reset(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
    Engine::setView(uiView);
    hudManager = makeUiEntity();
    auto h = hudManager->addComponent<HUDManager>();

    //zombieSpawner = new ZombieSpawner({0, 0, 800, 600}, 2.0f);

	// Set load to true when finished.
	setLoaded(true);

    // fade in
    Engine::_gameState = GameStates::PREPARE;
}

void TestScene::UnLoad() {
	Scene::UnLoad();
}

void TestScene::Update(const double& dt) {
    if (!isLoaded()) return;

	if (!player->isAlive()) {
        Engine::_gameState = GameStates::GAMEOVER;
	}

	if (Engine::_gameState != GameStates::PAUSE) {
		if (Keyboard::isKeyPressed(Keyboard::P)){
            Engine::_gameState = GameStates::PAUSE;
		}
        if (Keyboard::isKeyPressed(Keyboard::W) && Engine::_gameState == GameStates::PREPARE) {
            Engine::_gameState = GameStates::WAVE;
        }

        gameView.setCenter(player->getPosition());

        if (Engine::_gameState == GameStates::WAVE) {
            //zombieSpawner->update(dt);
        } else {

        }

		Scene::Update(dt);
        ents.update(dt);
        
        ui_ents.update(dt);
	}

    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
        //Engine::ChangeScene(&menu);
        //this->UnLoad();
    }
    //render_end();
}

void TestScene::Render() {
    if (!isLoaded()) return;

    Engine::setView(gameView);
    //ls::renderFloor(Engine::GetWindow());
    ents.render();
	Scene::Render();

    Engine::setView(uiView);
    ui_ents.render();
    if (Engine::_gameState == GameStates::PAUSE) {

    }

    Engine::setView(gameView);
}