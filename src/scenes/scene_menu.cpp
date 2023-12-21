#include "scene_menu.h"
#include "../last_light.h"
#include "../engine/system_resources.h"
#include "../components/ui/cmp_text.h"
#include "../audio_manager.h"
#include "../engine/system_renderer.h"
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

void MenuScene::Load() {
    AudioManager::get_instance().playMusic("Cold-Moon.ogg", true, 0.5f);

    menuView = Engine::GetWindow().getDefaultView();
    menuView.reset(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
    Engine::setView(menuView);

    auto background = makeUiEntity("background");
    background->setPosition(Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 2.0f));
    auto b = background->addComponent<SpriteComponent>();
    b -> setTexture(Resources::get<Texture>("background.png"));

	auto txt= makeUiEntity();
	auto t = txt->addComponent<TextComponent>(menuView.getSize().x / 2.0f, menuView.getSize().y / 5.0f, "Last Light", "resident_evil_4_remake_font_by_snakeyboy_df7kacs.ttf");
    t->setTextSize(200);
    t->setColor(sf::Color::Yellow);

    btnStart = makeUiEntity();
    auto btn3Pos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 2.5);
    auto button3 = btnStart->addComponent<Button>(btn3Pos, "Play", sf::Color::White, sf::Color::Green, sf::Color::Red, false,[this] { startGame(); });

	btnSetting = makeUiEntity();
	auto btn2Pos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 1.8f);
	auto button2 = btnSetting->addComponent<Button>(btn2Pos, "Settings", sf::Color::White, sf::Color::Green, sf::Color::Red, false, [this] { openSettings(); });

    btnExit = makeUiEntity();
    auto btnPos = Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 1.1f);
    auto button = btnExit->addComponent<Button>(btnPos, "Exit", sf::Color::White, sf::Color::Green, sf::Color::Red, false, [this] { exitGame(); });

	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
    if (!isLoaded()) return;

    ui_ecm.update(dt);
}

void MenuScene::Render() {
    if (!isLoaded()) return;

    ui_ecm.render();
    Renderer::render();
}

void MenuScene::startGame() {
    Engine::ChangeScene(&testScene);
}

void MenuScene::openSettings() {

}

void MenuScene::exitGame() {
    Engine::GetWindow().close();
}



