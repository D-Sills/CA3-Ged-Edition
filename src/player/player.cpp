
#include "player.h"
#include "../engine/scene.h"
#include "../engine/system_resources.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_actor_movement.h"

using namespace std;
using namespace sf;

player::player(Scene* s) {
    player = makeEntity();
    playerSpriteIdle = make_shared<Texture>();
    playerSpriteMoving = make_shared<Texture>();
    playerRect = IntRect();
    playerSpriteIdle = Resources::get<Texture>("Idle.png");
    playerSpriteMoving = Resources::get<Texture>("Run.png");

    _sprite->setTexture(playerSpriteIdle);

    auto pspriteBounds = Vector2f(_sprite->getSprite().getTextureRect().width * 0.5f, _sprite->getSprite().getTextureRect().height * 0.5f);
    _sprite->getSprite().setOrigin(75, 75);
    _sprite->getSprite().setScale(2, 2);

    auto panimation = player->addComponent<AnimationComponent>();
    panimation->setAnimation(8, 0.1, playerSpriteIdle, playerRect);

    _movement->setSpeed(_speed);

    auto pshooting = player->addComponent<ShootingComponent>();
}

player::Update() {

}
