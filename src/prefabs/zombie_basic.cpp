
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
    std::cout << "Zombie init" << std::endl;
    _parent->addTag("enemy");
    //_parent->setPosition(sf::Vector2f (10000, 10000));
    // Add a Sprite Component
    _spriteComp = _parent->addComponent<SpriteComponent>();
    auto tex = Resources::load<Texture>("crawler.png");
    if (tex) {
        _spriteComp->setTexture(tex);
    }

    // Add a Collider Component
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Change as needed
    bodyDef.position.Set(_parent->getPosition().x / Physics::PIXEL_PER_METER , _parent->getPosition().y / Physics::PIXEL_PER_METER);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(32.0f / Physics::PIXEL_PER_METER, 32.0f / Physics::PIXEL_PER_METER);  // Change as needed

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;



    _collider = _parent->addComponent<ColliderComponent>(bodyDef, fixtureDef);

    // Add a Character Movement Component
    _pathfinding = _parent->addComponent<ZombieAIComponent>(10, 5);

    _controller = _parent->addComponent<CharacterControllerComponent>(bodyDef, fixtureDef);

    // Add a Character Component
    _character = _parent->addComponent<CharacterComponent>();

    // Load from CSV
    //uto stats = DataReader::readStatsFromCSV("path/to/file.csv");
    //auto health = stats["zombie_basic"].attributes["health"];
    //auto speed = stats["zombie_basic"].attributes["speed"];

    //_controller->setSpeed(speed);
    _character->setHealth(10);
    _character->setDamage(10);

}