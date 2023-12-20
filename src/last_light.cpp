#include "engine/engine.h"
#include "last_light.h"
using namespace sf;
using namespace std;

TestScene testScene;
MenuScene menuScene;
int volume;
Vector2i resolution;

int main() {
	resolution = Vector2i(1280, 720);
	Engine::Start(resolution.x, resolution.y, "Last Light", &menuScene);
}