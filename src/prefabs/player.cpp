
#include "player.h"

#include "../engine/system_resources.h"
#include "DataReader.h"
#include "maths.h"
#include "../engine/system_physics.h"
#include "../audio_manager.h"

using namespace std;
using namespace sf;

Player::Player(Entity* p, const std::shared_ptr<HUDManager>& h): Component(p) , _hud(h) {
    _parent->addTag("player");

    _spriteComp = _parent->addComponent<SpriteComponent>();
    _spriteComp->setTexture(Resources::load<Texture>("player.png"));

    // Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(_parent->getPosition().x / Physics::PIXEL_PER_METER , _parent->getPosition().y / Physics::PIXEL_PER_METER);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(32.0f / Physics::PIXEL_PER_METER, 32.0f / Physics::PIXEL_PER_METER);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    _body = Physics::GetWorld()->CreateBody(&bodyDef);
    _body->CreateFixture(&fixtureDef);
    _body->SetUserData(_parent);
    _body->SetLinearDamping(1);

    _parent->setOnCollision([this](Entity* e) { onCollisionEnter(e); });

    // Add a Character Movement Component
    _controller = _parent->addComponent<CharacterControllerComponent>(_body);

    // Add a Character Component
    _character = _parent->addComponent<CharacterComponent>();

    // Add a Projectile Emitter Component
    _projectileEmitter = _parent->addComponent<ProjectileEmitterComponent>();
    switchWeapon(WeaponType::PISTOL);

    // Add an Animator Component
    setupAnimations();
    _animator = _parent->addComponent<AnimatorComponent>();
    _animator->setAnimation(_idle);

    // Load from CSV
    //auto stats = DataReader::readStatsFromCSV("path/to/file.csv");
     //auto health = stats["Player"].attributes["health"];
     //auto speed = stats["Player"].attributes["speed"];

    _controller->setSpeed(5);
    _character->setHealth(100);
    _character->setMaxHealth(100);
    _character->setDamage(10);

    _hud->updateValues(_character->getHealth(), _character->getMaxHealth(), currentPistolCount, pistolAmmo, 0, 0, 0);
}

void Player::update(double dt) {
    if (_currentState == PlayerState::DEAD) return;
    if (_character->getHealth() <= 0) {
        die();
    }

    if (invincibilityTimer > 0) {
        // flash sprite
        if (invincibilityTimer > 0.4f) {
            _spriteComp->getSprite().setColor(Color::Transparent);
        } else if (invincibilityTimer > 0.3f) {
            _spriteComp->getSprite().setColor(Color::White);
        } else if (invincibilityTimer > 0.2f) {
            _spriteComp->getSprite().setColor(Color::Transparent);
        } else if (invincibilityTimer > 0.1f) {
            _spriteComp->getSprite().setColor(Color::White);
        }
        invincibilityTimer -= dt;
    }

    if (Mouse::isButtonPressed(Mouse::Right)) { // Key to enter aiming mode
        startAiming();
    } else {
        stopAiming();
    }

    // Calculate the position of the mouse relative to the world
    auto mousePosWindow = Mouse::getPosition(Engine::GetWindow());
    auto mousePosView = Engine::GetWindow().mapPixelToCoords(mousePosWindow);

    // Calculate the position of the parent entity
    auto pos = _parent->getPosition();
    auto angleRadians = atan2(mousePosView.y - pos.y, mousePosView.x - pos.x);
    auto angleDegrees = angleRadians * 180.0f / M_PI;
    _parent->setRotation(angleDegrees);

    if (_currentState == PlayerState::AIMING) {
        _controller->setSpeed(1);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            // shoot
            if (!isReloading || currentWeapon == WeaponType::PISTOL && currentPistolCount <= 0 || currentWeapon == WeaponType::SHOTGUN && currentShotgunCount <= 0 || currentWeapon == WeaponType::RIFLE && currentRifleCount <= 0) {
                startReloading();
            } else {
                if (_projectileEmitter->fireProjectile(_parent->getPosition(), angleRadians)) {
                    if (currentWeapon == WeaponType::PISTOL) {
                        AudioManager::get_instance().playSound("pistol shot");
                    } else if (currentWeapon == WeaponType::SHOTGUN) {
                        AudioManager::get_instance().playSound("shotgun shot");
                    } else if (currentWeapon == WeaponType::RIFLE) {
                        AudioManager::get_instance().playSound("ar shot");
                    }

                    if (currentWeapon == WeaponType::PISTOL) {
                        currentPistolCount--;
                        _hud->setAmmo(currentPistolCount, pistolAmmo);
                    } else if (currentWeapon == WeaponType::SHOTGUN) {
                        currentShotgunCount--;
                        _hud->setAmmo(currentShotgunCount, shotgunAmmo);
                    } else if (currentWeapon == WeaponType::RIFLE) {
                        currentRifleCount--;
                        _hud->setAmmo(currentRifleCount, rifleAmmo);
                    }
                }
            }
        }
    } else {
        _controller->setSpeed(5);
    }

    if (isReloading) {
        _currentState = PlayerState::RELOADING;
        reloadTimer += dt;
        _controller->setSpeed(1);
        if (reloadTimer >= reloadTime) {
            reload();
            isReloading = false;
            reloadTimer = 0.0f;
        }
    }

    // Handle manual reload
    if (Keyboard::isKeyPressed(Keyboard::R) && !isReloading) {
        startReloading();
        _controller->setSpeed(1);
        _currentState = PlayerState::RELOADING;
    }

    // Handle interaction with a cooldown
    //interactTimer += dt;
   // if (Keyboard::isKeyPressed(Keyboard::E) && interactTimer >= interactCooldown) {
   //     _currentState = PlayerState::INTERACTING;
   //     interact();
   //     interactTimer = 0.0f;
   //     _controller->setSpeed(1);
  //  }

    // movement
    if (Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _controller->move(Vector2f(0, -1));
        if (_currentState != PlayerState::AIMING && _currentState != PlayerState::RELOADING && _currentState != PlayerState::INTERACTING) {
            _currentState = PlayerState::WALKING;
        }
    }
    if (Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _controller->move(Vector2f(0, 1));
        if (_currentState != PlayerState::AIMING && _currentState != PlayerState::RELOADING && _currentState != PlayerState::INTERACTING) {
            _currentState = PlayerState::WALKING;
        }
    }
    if (Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _controller->move(Vector2f(-1, 0));
        if (_currentState != PlayerState::AIMING && _currentState != PlayerState::RELOADING && _currentState != PlayerState::INTERACTING) {
            _currentState = PlayerState::WALKING;
        }
    }
    if (Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _controller->move(Vector2f(1, 0));
        if (_currentState != PlayerState::AIMING && _currentState != PlayerState::RELOADING && _currentState != PlayerState::INTERACTING) {
            _currentState = PlayerState::WALKING;
        }
    }

    if (_controller->isMoving()) {
        footstepTimer += dt;
        if (footstepTimer >= footstepInterval) {
            AudioManager::get_instance().playSound("footstep");
            footstepTimer = 0.0f;
        }
    } else {
        footstepTimer = 0.0f;
    }

    if (_currentState != PlayerState::RELOADING && _currentState != PlayerState::INTERACTING && _currentState != PlayerState::AIMING) {
        if (Keyboard::isKeyPressed(Keyboard::Num1) && currentWeapon != WeaponType::PISTOL) {
            AudioManager::get_instance().playSound("equip pistol");
            switchWeapon(WeaponType::PISTOL);
            _hud->setAmmo(currentPistolCount, pistolAmmo);
            _hud->setWeaponIcon(Resources::load<Texture>("pistol.png"));
        }
        if (Keyboard::isKeyPressed(Keyboard::Num2) && currentWeapon != WeaponType::SHOTGUN) {
            AudioManager::get_instance().playSound("equip shotgun");
            switchWeapon(WeaponType::SHOTGUN);
            _hud->setAmmo(currentShotgunCount, shotgunAmmo);
            _hud->setWeaponIcon(Resources::load<Texture>("shotgun.png"));
        }
        if (Keyboard::isKeyPressed(Keyboard::Num3) && currentWeapon != WeaponType::RIFLE) {
            AudioManager::get_instance().playSound("equip ar");
            switchWeapon(WeaponType::RIFLE);
            _hud->setAmmo(currentRifleCount, rifleAmmo);
            _hud->setWeaponIcon(Resources::load<Texture>("ar.png"));
        }
    }

    // Update the animator
    switch (_currentState) {
        case PlayerState::IDLE:
            _animator->setAnimation(_idle);
            break;
        case PlayerState::WALKING:
            _animator->setAnimation(_walk);
            break;
        case PlayerState::AIMING:
            _animator->setAnimation(_aim);
            break;
        case PlayerState::RELOADING:
            _animator->setAnimation(_reload);
            break;
        case PlayerState::INTERACTING:
            _animator->setAnimation(_interact);
            break;
    }
}

void Player::startReloading() {
    isReloading = true;
    reloadTimer = 0.0f;
    std::cout << "Reloading..." << std::endl;
    AudioManager::get_instance().playSound("reload");
}

void Player::reload() {
    if (currentWeapon == WeaponType::PISTOL) {
        pistolAmmo -= pistolAmmoMax - currentPistolCount;
        currentPistolCount = pistolAmmoMax;
        _hud->setAmmo(currentPistolCount, pistolAmmo);
    } else if (currentWeapon == WeaponType::SHOTGUN) {
        currentShotgunCount = shotgunAmmoMax;
        _hud ->setAmmo(currentShotgunCount, shotgunAmmo);
    } else if (currentWeapon == WeaponType::RIFLE) {
        currentRifleCount = rifleAmmoMax;
        _hud->setAmmo(currentRifleCount, rifleAmmo);
    }
    std::cout << "Reloaded" << std::endl;
}

void Player::interact() {
    _currentState = PlayerState::INTERACTING;
    std::cout << "Interacted" << std::endl;
}

void Player::startAiming() {
    AudioManager::get_instance().playSound("aim");
    _currentState = PlayerState::AIMING;
}

void Player::stopAiming() {
    _currentState = PlayerState::IDLE;
}

void Player::render() {}

void Player::setupAnimations() {
    // 6 frame walk animation
    vector<Frame> walkFrames;
    for (int i = 0; i < 6; ++i) {
        Frame frame;
        frame.rect = IntRect(i * 35, 0, 35, 57);
        frame.duration = 1.0f / 6.0f; // 6 frames should add up to 1 second
        walkFrames.push_back(frame);
    }
    auto texture= Resources::load<Texture>("player_walk.png");
    _walk = Animation(texture,walkFrames);

    // 1 frame idle animation
    vector<Frame> idleFrames;
    Frame frame;
    frame.rect = IntRect(0, 0, 35, 57);
    frame.duration = 1.0f;
    idleFrames.push_back(frame);
    texture = Resources::load<Texture>("player_idle.png");
    _idle = Animation(texture, idleFrames);

    // 1 frame aim animation
    vector<Frame> aimFrames;
    frame.rect = IntRect(0, 0, 66, 57);
    frame.duration = 1.0f;
    aimFrames.push_back(frame);
    texture = Resources::load<Texture>("player_aim.png");
    _aim = Animation(texture, aimFrames);

    // 1 frame interact animation
    vector<Frame> interactFrames;
    frame.rect = IntRect(0, 0, 35, 57);
    frame.duration = 1.0f;
    interactFrames.push_back(frame);
    texture = Resources::load<Texture>("player_interact.png");
    _interact = Animation(texture, interactFrames);

    // 5 frame reload animation
    vector<Frame> reloadFrames;
    for (int i = 0; i < 5; ++i) {
        Frame frame;
        frame.rect = IntRect(i * 63, 0, 63, 57);
        frame.duration = 1.0f / 5.0f; // 5 frames should add up to 1 second
        reloadFrames.push_back(frame);
    }
    texture = Resources::load<Texture>("player_reload.png");
    _reload = Animation(texture, reloadFrames);
}

void Player::applyPickup(int amount, PickupType type) {
    switch (type) {
        case PickupType::HEALTH:
            _character->setHealth(_character->getHealth() + amount);
            break;
        case PickupType::PISTOL_AMMO:
            pistolAmmo += amount;
            if (currentWeapon == WeaponType::PISTOL) {
                _hud->setAmmo(currentPistolCount, pistolAmmo);
            }
            break;
        case PickupType::SHOTGUN_AMMO:
            shotgunAmmo += amount;
            if (currentWeapon == WeaponType::SHOTGUN) {
                _hud->setAmmo(currentShotgunCount, shotgunAmmo);
            }
            break;
        case PickupType::RIFLE_AMMO:
            rifleAmmo += amount;
            if (currentWeapon == WeaponType::RIFLE) {
                _hud->setAmmo(currentRifleCount, rifleAmmo);
            }
            break;
        case PickupType::XP:
            addXP(amount);
            _hud->setExp(currentXP);
            break;
    }
}

void Player::addXP(float amount) {
    currentXP += amount;
    if (currentXP >= 100) {
        currentXP -= 100;
        score += amount;
        level++;
        Engine::_gameState = GameStates::UPGRADE;
        _hud->setScore(score);
        //Engine::_activeScene->getEcm().find("hudManager")[0]->get_components<HUDManager>()[0]->addUpgradePoint();
    }
}

void Player::applyUpgrade(float amount, UpgradeType type) {
    switch (type) {
        case UpgradeType::HEALTH:
            _character->setHealth(_character->getHealth() + amount);
            break;
        case UpgradeType::SPEED:
            _controller->setSpeed(_character->getSpeed() + amount);
            break;
        case UpgradeType::DAMAGE:
            _character->setDamage(_character->getDamage() + amount);
            break;
    }
}

void Player::takeDamage(int damage) {
    if (_currentState == PlayerState::DEAD) return;
    if (invincibilityTimer > 0) return;
    _character->setHealth(_character->getHealth() - damage);
    // set invincibility frames
    invincibilityTimer = 0.5f;
    AudioManager::get_instance().playSound("hit");
    AudioManager::get_instance().playSound("player take damage");
    _hud->setHealth(_character->getHealth(), _character->getMaxHealth());
}

void Player::switchWeapon(WeaponType type) {
    switch (type) {
        case WeaponType::PISTOL:
            currentWeapon = WeaponType::PISTOL;
            _projectileEmitter->setFireRate(0.5f);
            _projectileEmitter->setProjectileDamage(10);
            _projectileEmitter->setProjectileSpeed(500.0f);
            break;
        case WeaponType::SHOTGUN: // should be spread but not bothered
            currentWeapon = WeaponType::SHOTGUN;
            _projectileEmitter->setFireRate(1.0f);
            _projectileEmitter->setProjectileDamage(20);
            _projectileEmitter->setProjectileSpeed(100.0f);
            break;
        case WeaponType::RIFLE:
            currentWeapon = WeaponType::RIFLE;
            _projectileEmitter->setFireRate(0.1f);
            _projectileEmitter->setProjectileDamage(5);
            _projectileEmitter->setProjectileSpeed(1000.0f);
            break;
    }
}

void Player::die() {
    _currentState = PlayerState::DEAD;
    AudioManager::get_instance().playSound("player death");
    _character->setHealth(0);
    _parent->setForDelete();
    Engine::_gameState = GameStates::GAMEOVER;
}

void Player::onCollisionEnter(Entity *other) const {
    if (other->hasTag("enemy")) {
        _character->setHealth(_character->getHealth() - 10);
    }
}


