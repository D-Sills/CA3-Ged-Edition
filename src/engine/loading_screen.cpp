#include "loading_screen.h"
#include "maths.h"
#include "engine.h"
#include "system_resources.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

static float loadingSpinner = 0.f;
static float loadingTime;
static bool isLoading = false;

void LoadingScreen::Update(float dt, const Scene* const scn) {
    //  cout << "Eng: Loading Screen\n";
    if (scn->isLoaded()) {
        cout << "Eng: Exiting Loading Screen\n";
        isLoading = false;
    }
    else {
        loadingSpinner += 400.0f * dt;
        loadingTime += dt;
    }
}

void LoadingScreen::Render() {
    // cout << "Eng: Loading Screen Render\n";

    static Sprite background;
    auto backTexture = Resources::get<Texture>("Space_Background.png");
    background.setTexture(*backTexture);

    static CircleShape octagon(100);
    octagon.setOrigin(Vector2f(100, 100));
    octagon.setRotation(deg2rad(loadingSpinner));
    octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
    auto tex = new Texture();
    tex->loadFromFile("res/img/Terran.png");
    octagon.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));
    octagon.setTexture(tex);

    static Text t("Loading", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
    t.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));
    t.setOutlineThickness(2);
    t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.5f, 0.3f));
    t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width / 2.0f,
                t.getLocalBounds().top + t.getLocalBounds().height / 2.0f);
    Renderer::queue(&background);
    Renderer::queue(&t);
    Renderer::queue(&octagon);
}

void LoadingScreen::Load() {
    cout << "Eng: Loading Screen Load\n";
    loadingSpinner = 0.f;
    loadingTime = 0.f;
    isLoading = true;
}

bool LoadingScreen::IsLoading() { return isLoading; }



