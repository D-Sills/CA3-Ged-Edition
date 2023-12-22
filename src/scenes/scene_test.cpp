#include "../last_light.h"
#include "../engine/system_resources.h"
#include "scene_test.h"
#include "../engine/system_renderer.h"
#include "../prefabs/player.h"
#include "../prefabs/crosshair.h"
#include "../prefabs/pause.h"
#include "LevelSystem.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void TestScene::Load() {
    //LevelSystem::loadLevelFile("res/levels/smallFloorMap.txt", 32.0f);

    //HUD Variables
    uiView = Engine::GetWindow().getDefaultView();
    uiView.reset(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
    hudManager = makeUiEntity();
    auto h = hudManager->addComponent<HUDManager>();

    gameView = Engine::GetWindow().getDefaultView();
    gameView.reset(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
    player = makeEntity();
    player->setPosition({400, 300});
    auto p = player->addComponent<Player>(h);
    gameView.setCenter(player->getPosition());


    crosshair = makeEntity();
    auto c = crosshair->addComponent<Crosshair>();

    pause = makeUiEntity();
    auto p2 = pause->addComponent<Pause>();

    zombieSpawner = new ZombieSpawner({0, 0, 800, 600}, 8.0f);

	setLoaded(true);

    // fade in
    Engine::_gameState = GameStates::PREPARE;

}

void TestScene::Update(const double& dt) {
    if (!isLoaded()) return;

    if (Engine::_gameState == GameStates::GAMEOVER) {
        Engine::ChangeScene(&menuScene);
        this->UnLoad();
    }

    if (Engine::_gameState == GameStates::GAMEOVER) {
        return;
    }

    auto h = hudManager->get_components<HUDManager>()[0];
    timer += dt;
    h->setTimer(timer);

    if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::P)) {
        // need to add a buffer to prevent multiple presses
        pause->setVisible(!pause->isVisible());

        if (pause->isVisible()) {
            Engine::GetWindow().setMouseCursorVisible(true);
            Engine::_gameState = GameStates::PAUSE;
        } else {
            Engine::GetWindow().setMouseCursorVisible(false);
            Engine::_gameState = GameStates::WAVE;
        }
    }

	if (Engine::_gameState != GameStates::PAUSE) {
        if (Keyboard::isKeyPressed(Keyboard::W) && Engine::_gameState == GameStates::PREPARE) {
            Engine::_gameState = GameStates::WAVE;
            NextWave();
            std::cout << "WAVE STARTED" << std::endl;
        }

        gameView.setCenter(player->getPosition());

        if (Engine::_gameState == GameStates::WAVE) {
            zombieSpawner->update(dt);
        } else {

        }

        ecm.update(dt);
        ui_ecm.update(dt);
	}

    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
        Engine::ChangeScene(&menuScene);
        this->UnLoad();
    }
}

void TestScene::Render() {
    if (!isLoaded()) return;

    Engine::setView(gameView);
    //LevelSystem::render(Engine::GetWindow());
    ecm.render();
    Renderer::render();

    Engine::setView(uiView);
    ui_ecm.render();
    Renderer::render();

    Engine::setView(gameView);
}

void TestScene::NextWave() {
    auto h = hudManager->get_components<HUDManager>()[0];
    zombieSpawner->startWave();
}

