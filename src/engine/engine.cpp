#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "loading_screen.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include "scene.h"
#include "../audio_manager.h"

using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;
AStar::Generator Engine::generator;
GameStates Engine::_gameState;

static RenderWindow* _window;

float frameTimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	{
        frameTimes[++ftc] = dt;
		static string avg = _gameName + " FPS:";
		if (ftc % 60 == 0) {
			double d = 0;
			for (const auto t : frameTimes) {
                d += t;
			}
            d = 1.0 / (d / 255.0);
			_window->setTitle(avg + toStrDecPt(2, d));
		}
	}

	if (LoadingScreen::IsLoading()) {
		LoadingScreen::Update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		Physics::update(dt);
		_activeScene->Update(dt);
	}
    AudioManager::get_instance().update(dt);

    Physics::processDestructionQueue();
}

void Engine::Render(RenderWindow& window) {
	if (LoadingScreen::IsLoading()) {
		LoadingScreen::Render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
	}

	//Renderer::render(); // that drop pod project was garbage
}

void Engine::Start(unsigned int width, unsigned int height,
	const std::string& gameName, Scene* scn) {
	RenderWindow window(VideoMode(width, height), gameName);
	//window.setVerticalSyncEnabled(true);
	_gameName = gameName;
	_window = &window;
	Renderer::initialise(window);
    Physics::initialise();
    AudioManager::get_instance().init();
    AudioManager::get_instance().setMasterVolume(100);
	ChangeScene(scn);

	while (window.isOpen()) {
		Event event{};
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.clear();
		Update();
		Render(window);
		window.display();
	}
	if (_activeScene != nullptr) {
		_activeScene->UnLoad();
		_activeScene = nullptr;
	}

	window.close();
	Physics::shutdown();
	// Render::shutdown();
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::setView(View v) { _window->setView(v); }

void Engine::moveView(View view,Vector2f pos) {
    view.setCenter(pos);
}

// CHANGE RES PART
void Engine::changeResolution(int x, int y)
{
	Vector2f _newResolution(x, y);
	_window->create(VideoMode(_newResolution.x, _newResolution.y), "Last Light");
}

void Engine::ChangeScene(Scene* s) {
	cout << "Eng: changing scene: " << s << endl;
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad(); // todo: Unload Async
	}

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";

        LoadingScreen::Load();
        _activeScene->LoadAsync();
	}
}

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
	// Return time since Epoc
	long long now() {
		return std::chrono::high_resolution_clock::now()
			.time_since_epoch()
			.count();
	}
	// Return time since last() was last called.
	long long last() {
		auto n = now();
		static auto then = now();
		auto dt = n - then;
		then = n;
		return dt;
	}
} // namespace timing