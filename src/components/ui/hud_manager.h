#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "cmp_bar.h"
#include "cmp_text.h"
#include "../cmp_sprite.h"


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
