
#include "player.h"

#include "../engine/system_resources.h"
#include "DataReader.h"
#include "../last_light.h"
#include "maths.h"
#include "../engine/system_physics.h"

using namespace std;
using namespace sf;

Player::Player(Entity* p): Component(p) {
    // Add a Sprite Component
    _spriteComp = _parent->addComponent<SpriteComponent>();
    auto tex = Resources::load<Texture>("player.png");
    if (tex) {
        std::cout << "Loaded player texture" << std::endl;
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
    _controller = _parent->addComponent<CharacterControllerComponent>(bodyDef, fixtureDef);

    // Add a Character Component
    _character = _parent->addComponent<CharacterComponent>();

    // Add a Projectile Emitter Component
    _projectileEmitter = _parent->addComponent<ProjectileEmitterComponent>(0.5f, 100.0f, 10);



    // Load from CSV
    //auto stats = DataReader::readStatsFromCSV("path/to/file.csv");
   // auto health = stats["Player"].attributes["health"];
    //auto speed = stats["Player"].attributes["speed"];

    _controller->setSpeed(2);
    _character->setHealth(50);
    _character->setDamage(10);

    currentBullet = bulletMax;

}

void Player::update(double dt) {
    //update view on player

    // movement
    if (Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _controller->move(Vector2f(0, -1));
    }
    if (Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _controller->move(Vector2f(0, 1));
    }
    if (Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _controller->move(Vector2f(-1, 0));
    }
    if (Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _controller->move(Vector2f(1, 0));
    }

    //std::cout << "Player position: " << _parent->getPosition().x << ", " << _parent->getPosition().y << std::endl;
    // Calculate the position of the mouse relative to the world
    auto mousePosWindow = Mouse::getPosition(Engine::GetWindow()); // Mouse position relative to the window
    auto mousePosView = Engine::GetWindow().mapPixelToCoords(mousePosWindow); // Convert to world coordinates

// Calculate the position of the parent entity
    auto pos = _parent->getPosition();

// Calculate the angle between the entity and the mouse position
// atan2 returns the angle in radians, with the y-axis going downward
    auto angleRadians = atan2(mousePosView.y - pos.y, mousePosView.x - pos.x);

// Convert the angle to degrees
    auto angleDegrees = angleRadians * 180.0f / M_PI;

// SFML's setRotation expects 0 degrees to be facing right, and positive angles go clockwise
// So we adjust by -90 degrees to make 0 degrees face upwards
    _parent->setRotation(angleDegrees);


    if (Mouse::isButtonPressed(Mouse::Left)) {
        // shoot
        if (currentBullet <= 0) {
            // reload
        } else {
            if (_projectileEmitter->fireProjectile(_parent->getPosition(), angleRadians)) {
                std::cout << "Fired projectile" << std::endl;
                currentBullet--;
            }
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::R)) {
        // reload
    }

    if (Keyboard::isKeyPressed(Keyboard::E)) {
        // interact with object
    }
}

void Player::render() {

}

