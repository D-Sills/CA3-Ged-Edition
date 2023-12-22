#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "../components/ui/cmp_text.h"
#include "../components/ui/cmp_bar.h"
#include "../components/cmp_sprite.h"
#include "../components/ui/cmp_ui_sprite.h"


class HUDManager : public Component {
public:
    explicit HUDManager(Entity* p);

    void update(double dt) override {}

    void render() override {}

    // Methods to manipulate HUD elements
    void setHealth(float health, float maxHealth);
    void setAmmo(int ammo, int maxAmmo);
    void setTimer(float time);
    void setScore(int score);
    void setWeaponIcon(const std::shared_ptr<sf::Texture>& texture);
    void setWave(int wave);
    void setExp(float xp);

    void updateValues(float health, float maxHealth, int ammo, int maxAmmo, float time, int score, int wave);

private:
    std::shared_ptr<UIBarComponent> _healthBar;
    std::shared_ptr<UIBarComponent> _expBar;
    std::shared_ptr<TextComponent> _ammoText;
    std::shared_ptr<TextComponent> _timerText;
    std::shared_ptr<TextComponent> _waveText;
    std::shared_ptr<TextComponent> _scoreText;
    std::shared_ptr<UISpriteComponent> _weaponIcon;
};
