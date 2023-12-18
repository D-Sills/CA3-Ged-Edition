
#include "player.h"

#include "../engine/system_resources.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_character_controller.h"
#include "DataReader.h"
#include "../last_light.h"
#include "maths.h"
#include "../engine/system_physics.h"

using namespace std;
using namespace sf;

Player::Player(Scene *const s, sf::Vector2f position) {
    _player = s->makeEntity();
    _player->setPosition(position);

    // Add a Sprite Component
    _spriteComp = _player->addComponent<SpriteComponent>();
    _spriteComp->init(Resources::get<Texture>("player.png"));

    // Add an Animation Component
    _animator = _player->addComponent<AnimatorComponent>();

    // Add a Collider Component
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Change as needed
    bodyDef.position.Set(_player->getPosition().x / PIXEL_PER_METER, _player->getPosition().y / PIXEL_PER_METER);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);  // Set box size

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    _collider = _player->addComponent<ColliderComponent>(bodyDef, fixtureDef);

    // Add a Character Movement Component
    _controller = _player->addComponent<CharacterControllerComponent>();
    _controller->setSpeed(100.0f);

    // Add a Character Component
    _character = _player->addComponent<CharacterComponent>();

    // Add a Projectile Emitter Component
    _projectileEmitter = _player->addComponent<ProjectileEmitterComponent>(10, 0.5f, 100.0f, 10);

    // Set up the components
    _idle = Resources::get<Texture>("player.png");
    _spriteComp->setTexture(_idle);

    // Set up animation frames
    Frame frame1(/* frame details */);
    Frame frame2(/* frame details */);
    // Add more frames as needed
    _animator->addFrame(frame1);
    _animator->addFrame(frame2);
    // ...

    // Load from CSV
    auto stats = DataReader::readStatsFromCSV("path/to/file.csv");
    auto health = stats["Player"].attributes["health"];
    auto speed = stats["Player"].attributes["speed"];

    _controller->setSpeed(speed);
    _character->setHealth(health);
    _character->setDamage(10);

}

void Player::update(double dt) {
    //update view on player


    _player->update(dt);

    // movement
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        ;
    }

    // spin to face mouse
    auto pos = _player->getPosition();
    auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));
    auto angle = atan2(mousePos.y - pos.y, mousePos.x - pos.x);
    _player->setRotation(deg2rad(angle) + 90);

    // shooting
    if (Mouse::isButtonPressed(Mouse::Left)) {
        _projectileEmitter->fireProjectile(_player->getPosition(), angle);
    }

    // animation
    if (_controller->getIsMoving()) {
        _animator->play();
    } else {
        _animator->stop();
    }

}

void Player::render() {
    //_player->render();
}

Entity *Player::getEntity() const {
    return _player.get();
}
