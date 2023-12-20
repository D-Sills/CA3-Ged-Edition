#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>
#include "AStar.hpp"

enum class GameStates {
    MENU,
    PREPARE,
    WAVE,
    PAUSE,
    GAMEOVER,
};

class Engine {
public:
    Engine() = delete;
    void operator=(Engine const&) = delete;

	static void Start(unsigned int width, unsigned int height,
		const std::string& gameName, Scene* scn);
	static void ChangeScene(Scene*);
	static sf::RenderWindow& GetWindow();
	static sf::Vector2u getWindowSize();
	static void setVsync(bool b);
	static void setView(sf::View);
	static void moveView(sf::View view,sf::Vector2f);
	static void changeResolution(int x, int y);
    static Scene* _activeScene;
    static AStar::Generator generator;
    static GameStates _gameState;

private:

	static std::string _gameName;
	static void Update();
	static void Render(sf::RenderWindow& window);
};

namespace timing {
	// Return time since Epoc
	long long now();
	// Return time since last() was last called.
	long long last();
} // namespace timing