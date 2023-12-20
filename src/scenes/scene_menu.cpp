#include "scene_menu.h"
#include "../last_light.h"
#include "LevelSystem.h"
#include <iostream>
#include "../engine/system_resources.h"
#include "../engine/system_renderer.h"
#include <SFML/Audio.hpp>

using namespace std;

void MenuScene::Load() {
    ui_ecm = new EntityManager();
    *ui_ecm = Scene::getUiEcm();

	menuView.reset(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
    Engine::setView(menuView);

	// set background
	auto backTexture = Resources::get<Texture>("background.png");
	background.setTexture(*backTexture);


	auto txt= makeUiEntity();
	auto pos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 5.0f);
	auto t = txt->addComponent<TextComponent>(menuView.getSize().x / 2.0f, menuView.getSize().y / 5.0f, "Last Light", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");

	btnExit = makeUiEntity();
	auto btnPos = Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 1);
	auto button = btnExit->addComponent<Button>(btnPos, "Exit", sf::Color::White, sf::Color::Green, sf::Color::Red);

	btnSetting = makeUiEntity();
	auto btn2Pos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 2.f);
	auto button2 = btnSetting->addComponent<Button>(btn2Pos, "Setting", sf::Color::White, sf::Color::Green, sf::Color::Red);

	btnStart = makeUiEntity();
	auto btn3Pos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 3.f);
	auto button3 = btnStart->addComponent<Button>(btn3Pos, "Play", sf::Color::White, sf::Color::Green, sf::Color::Red);

	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
    if (!isLoaded()) return;

	if (btnStart->GetCompatibleComponent<Button>()[0]->isPressed())
	{
        Engine::ChangeScene(&testScene);
		ls::setTextureMap("res/assets/tiles/grass.png");
		music.stop();
	}
	else if (btnSetting->GetCompatibleComponent<Button>()[0]->isPressed())
	{

	}
	else if (btnExit->GetCompatibleComponent<Button>()[0]->isPressed())
	{
		Engine::GetWindow().close();
	}

	if (!sf::Mouse::isButtonPressed(Mouse::Button::Left))
		//Button::_mouseState = BUTTON_IDLE;

	Scene::Update(dt);
    ui_ecm->update(dt);
}

void MenuScene::Render()
{
    if (!isLoaded()) return;

	Engine::setView(menuView);
    ui_ecm->render();
	Scene::Render();
}