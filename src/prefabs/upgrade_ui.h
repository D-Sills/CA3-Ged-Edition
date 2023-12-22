

#ifndef LASTLIGHT_UPGRADE_UI_H
#define LASTLIGHT_UPGRADE_UI_H


#include "ecm.h"
#include "../components/cmp_sprite.h"
#include "../components/ui/cmp_text.h"

class UpgradeMenu : public Component {
public:
    explicit UpgradeMenu(Entity* p);

    void update(double dt) override {}

    void render() override {}

private:
    std::shared_ptr<SpriteComponent> _background;
    std::shared_ptr<TextComponent> _text;
    std::shared_ptr<SpriteComponent> _weaponIcon;

};


#endif //LASTLIGHT_UPGRADE_UI_H
