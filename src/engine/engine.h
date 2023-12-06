#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

class Engine {
public:

	Engine() = delete;
	static void Start(unsigned int width, unsigned int height,
		const std::string& gameName, Scene* scn);
	static void ChangeScene(Scene*);
	static sf::RenderWindow& GetWindow();
	static sf::Vector2u getWindowSize();
	static void setVsync(bool b);
	static void setView(sf::View);
	static void moveView(sf::Vector2f);
	static void changeResolution(int x, int y);
    static Scene* _activeScene;
	static sf::Vector2f flocking(Entity* thisEnemy, sf::Vector2f toPlayer);

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