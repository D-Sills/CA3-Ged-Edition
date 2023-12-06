#include "engine/engine.h"
#include "last_light.h"
#include "scenes/scene_menu.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

MenuScene menu;
SettingsScene settings;
PlanetLevelScene planetLevel;
short unsigned switchState;
int volume;
Vector2i resolution;

int main() {
	resolution = Vector2i(1280, 720);
	volume = 20;
	Engine::Start(resolution.x, resolution.y, "Drop Pod", &menu);
}