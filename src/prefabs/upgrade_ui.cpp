#include "upgrade_ui.h"
#include "../engine/engine.h"
#include "../engine/system_resources.h"

UpgradeMenu::UpgradeMenu(Entity *p) : Component(p) {
    Engine::GetWindow().setMouseCursorVisible(true);
    _background = _parent->addComponent<SpriteComponent>();
    _background->setTexture(Resources::load<sf::Texture>("overlay.png"));


}