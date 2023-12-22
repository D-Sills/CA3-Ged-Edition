
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
    _parent->addTag("enemy");
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

    _body = Physics::GetWorld()->CreateBody(&bodyDef);
    _body->CreateFixture(&fixtureDef);
    _body->SetUserData(_parent);
    _body->SetLinearDamping(1);

    _parent->setOnCollision([this](Entity* e) { onCollisionEnter(e); });
}

void Zombie::init(Vector2f position) {
    _parent->setVisible(true);
    //
    // Add a Sprite Component

    _parent->setPosition(position);

    //_pathfinding = _parent->addComponent<ZombieAIComponent>(10, 5);

    //_controller = _parent->addComponent<CharacterControllerComponent>(_body);

    _character = _parent->addComponent<CharacterComponent>();

    // Load from CSV
    //uto stats = DataReader::readStatsFromCSV("path/to/file.csv");
    //auto health = stats["zombie_basic"].attributes["health"];
    //auto speed = stats["zombie_basic"].attributes["speed"];

    //_controller->setSpeed(speed);
    _character->setHealth(10);
    _character->setDamage(10);

}

void Zombie::update(double dt) { // not using the controller because i am sick of this assignment and extremely burnt out :)
    if (!_parent->isVisible()) return;

    auto playerPos = Engine::_activeScene->getEcm().find("player")[0]->getPosition();
    sf::Vector2f direction = playerPos - _parent->getPosition();

    // Normalize the direction
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude > 0) {
        direction /= magnitude;

        // Set Box2D body velocity
        float speed = 5.0f; // Adjust speed as needed
        _body->SetLinearVelocity(b2Vec2(direction.x * speed, direction.y * speed));
        _parent->setPosition(Vector2f(_body->GetPosition().x * Physics::PIXEL_PER_METER, _body->GetPosition().y * Physics::PIXEL_PER_METER));

        // Set rotation to face the player
        float angleRadians = atan2(direction.y, direction.x);
        _parent->setRotation(angleRadians * 180 / M_PI); // Convert to degrees
        std::cout << "Zombie position: " << _parent->getPosition().x << ", " << _parent->getPosition().y << std::endl;
    } else {
        _body->SetLinearVelocity(b2Vec2(0, 0));
    }
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

    if (_onRelease) {
        _onRelease();
    }
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
}

void Zombie::onCollisionEnter(Entity *other) {
    if (other->hasTag("bullet")) {
        auto bullet = other->get_components<ProjectileComponent>()[0];
        takeDamage(bullet->getDamage());
    }
    if (other->hasTag("player")) {
        auto player = other->get_components<Player>()[0];
        AudioManager::get_instance().playSound("player take damage");
        player->takeDamage(_character->getDamage());
    }
}

void Zombie::tearDown() {
    Physics::markBodyForDestruction(_body);
}