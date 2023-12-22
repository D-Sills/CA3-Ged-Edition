

#ifndef LASTLIGHT_UPGRADE_UI_H
#define LASTLIGHT_UPGRADE_UI_H


#include "ecm.h"
#include "../components/cmp_sprite.h"
#include "../components/ui/cmp_text.h"
#include "../components/ui/cmp_button.h"

class UpgradeMenu : public Component {
public:
    explicit UpgradeMenu(Entity* p);

    void update(double dt) override {}

    void render() override {}

private:
    std::shared_ptr<SpriteComponent> _background;
    std::shared_ptr<TextComponent> _text;
    std::shared_ptr<SpriteComponent> _health;
    std::shared_ptr<SpriteComponent> _speed;
    std::shared_ptr<SpriteComponent> _damage;
    std::shared_ptr<Button> _healthButton;
    std::shared_ptr<Button> _speedButton;
    std::shared_ptr<Button> _damageButton;

};


#endif //LASTLIGHT_UPGRADE_UI_H
