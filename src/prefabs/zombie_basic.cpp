
#include "zombie_basic.h"

#include "../engine/system_resources.h"
#include "DataReader.h"
#include "../last_light.h"
#include "maths.h"
#include "../engine/system_physics.h"
#include "../components/cmp_projectile.h"
#include "player.h"
#include "../audio_manager.h"
#include "pickup.h"

using namespace std;
using namespace sf;

Zombie::Zombie(Entity* p)
        : Component(p) {
    initialised = false;
    _spriteComp = _parent->addComponent<SpriteComponent>();
    _spriteComp->setTexture(Resources::load<Texture>("crawler.png"));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Change as needed
    bodyDef.position.Set(_parent->getPosition().x / Physics::PIXEL_PER_METER , _parent->getPosition().y / Physics::PIXEL_PER_METER);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(6.0f / Physics::PIXEL_PER_METER, 32.0f / Physics::PIXEL_PER_METER);  // Change as needed

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    _body = Physics::GetWorld()->CreateBody(&bodyDef);
    _body->CreateFixture(&fixtureDef);
    _body->SetUserData(_parent);
    _body->SetLinearDamping(1);

    _controller = _parent->addComponent<CharacterControllerComponent>(_body);

    _character = _parent->addComponent<CharacterComponent>();

    // random chance to be one of the 3 types of zombie
    int type = rand() % 3;

    // Load from CSV this works just not using it
    //auto stats = DataReader::readStatsFromCSV("path/to/file.csv");
    //_character->setMaxHealth(stats[type][0]);

    if (type == 0) {
        _spriteComp->setTexture(Resources::load<Texture>("crawler.png"));
        _xpValue = 10;
        _controller->setSpeed(3);
        _character->setHealth(10);
        _character->setDamage(5);
        _character->setMaxHealth(10);
    } else if (type == 1) {
        _spriteComp->setTexture(Resources::load<Texture>("chaser.png"));
        _xpValue = 20;
        _controller->setSpeed(5);
        _character->setHealth(20);
        _character->setDamage(10);
        _character->setMaxHealth(20);
    } else if (type == 2) {
        _spriteComp->setTexture(Resources::load<Texture>("bloater.png"));
        _xpValue = 30;
        _controller->setSpeed(2);
        _character->setHealth(30);
        _character->setDamage(15);
        _character->setMaxHealth(30);

    }


}

void Zombie::init(Vector2f position) {
    _parent->addTag("enemy");
    _parent->setVisible(true);
    //
    // Add a Sprite Component

    _parent->setPosition(position);
    std::cout << "Zombie position: " << _parent->getPosition().x << ", " << _parent->getPosition().y << std::endl;
    //_pathfinding = _parent->addComponent<ZombieAIComponent>(10, 5);






    _parent->setOnCollision([this](Entity* e) { onCollisionEnter(e); });


    initialised = true;

}

void Zombie::update(double dt) { // not using the controller because i am sick of this assignment and extremely burnt out :)
    if (!_parent->isVisible() || !initialised) return;

    auto playerPos = Engine::_activeScene->getEcm().find("player")[0]->getPosition();
    sf::Vector2f direction = playerPos - _parent->getPosition();

    if (direction != sf::Vector2f(0, 0)) {
        float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude; // Normalize the direction

        _controller->move(direction); // Use the controller to move towards the player
    }

    // Set rotation to face the player
    float angle = atan2(direction.y, direction.x);
    _parent->setRotation(angle * 180 / M_PI);
}



void Zombie::render() {}

void Zombie::setOnRelease(const std::function<void()>& onRelease) {
    _onRelease = onRelease;
}

void Zombie::die() {
    AudioManager::get_instance().playSound("zombie death scream");
    AudioManager::get_instance().playSound("zombie death");
    // give player xp
    auto player = Engine::_activeScene->getEcm().find("player")[0];
    auto p = player->get_components<Player>()[0];
    p->applyPickup(_xpValue, PickupType::XP);
    dropPickup();

    // spawn blood, should object pool this
    auto blood = Engine::_activeScene->makeEntity();
    blood->setPosition(_parent->getPosition());
    auto sprite = blood->addComponent<SpriteComponent>();
    sprite->setTexture(Resources::load<Texture>("blood.png"));
    tearDown();

    if (_onRelease) _onRelease();
}

void Zombie::dropPickup() {
    // 10% chance to drop pickup
    if (rand() % 10 != 0) return;

    auto pickup = Engine::_activeScene->makeEntity();
    pickup->setPosition(_parent->getPosition());
    auto pickupType = static_cast<PickupType>(rand() % 4);
    auto pickupComp = pickup->addComponent<Pickup>(pickupType);

}

void Zombie::attack() {}

void Zombie::takeDamage(int damage) {
    _character->setHealth(_character->getHealth() - damage);
    AudioManager::get_instance().playSound("hit");
    AudioManager::get_instance().playSound("zombie hit");
    if (_character->getHealth() <= 0) {
        die();
    }
    std::cout << "Zombie health: " << _character->getHealth() << std::endl;
}

void Zombie::onCollisionEnter(Entity *other) {
    if (!_parent->isVisible() || !initialised) return;

    if (other->hasTag("player")) {
        auto player = other->get_components<Player>()[0];
        if (player)
            player->takeDamage(_character->getDamage());
    }
}

void Zombie::tearDown() {
    _parent->setVisible(false);
    initialised = false;
    _parent->setOnCollision([](Entity* e) { return; });
    Physics::markBodyForDestruction(_body);

}