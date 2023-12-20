#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "components/ui/cmp_bar.h"
#include "components/ui/cmp_text.h"
#include "components/cmp_sprite.h"


class HUDManager : public Component {
public:
    explicit HUDManager(Entity* p);

    void update(double dt) override;
    void render() override;

    // Methods to manipulate HUD elements
    void setHealth(float health);
    void setAmmo(int ammo);
    void setTimer(float time);
    void setScore(int score);

private:
    std::shared_ptr<UIBarComponent> _healthBar;
    std::shared_ptr<TextComponent> _ammoText;
    std::shared_ptr<TextComponent> _timerText;
    std::shared_ptr<TextComponent> _scoreText;
    std::shared_ptr<SpriteComponent> _ammoIcon;
    std::shared_ptr<SpriteComponent> _crosshair;

};
