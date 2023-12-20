
#include "zombie_basic.h"

#include "../engine/system_resources.h"
#include "DataReader.h"
#include "../last_light.h"
#include "maths.h"
#include "../engine/system_physics.h"

using namespace std;
using namespace sf;

Zombie::Zombie(Entity* p)
        : Component(p) {
}

void Zombie::update(double dt) {
}

void Zombie::render() {
    //_player->render();
}

void Zombie::init() {
    _parent->setPosition(sf::Vector2f (100, 100));
    // Add a Sprite Component
    _spriteComp = _parent->addComponent<SpriteComponent>();
    _spriteComp->setTexture(Resources::get<Texture>("crawler.png"));

    // Add a Collider Component
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Change as needed
    bodyDef.position.Set(_parent->getPosition().x / Physics::PIXEL_PER_METER, _parent->getPosition().y / Physics::PIXEL_PER_METER);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);  // Set box size

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    _collider = _parent->addComponent<ColliderComponent>(bodyDef, fixtureDef);

    // Add a Character Movement Component
    _controller = _parent->addComponent<ZombieAIComponent>(10, 5);

    // Add a Character Component
    _character = _parent->addComponent<CharacterComponent>();

    // Set up the components
    _idle = Resources::get<Texture>("crawler.png");
    _spriteComp->setTexture(_idle);

    // Load from CSV
    //uto stats = DataReader::readStatsFromCSV("path/to/file.csv");
    //auto health = stats["zombie_basic"].attributes["health"];
    //auto speed = stats["zombie_basic"].attributes["speed"];

    //_controller->setSpeed(speed);
    _character->setHealth(10);
    _character->setDamage(10);

}