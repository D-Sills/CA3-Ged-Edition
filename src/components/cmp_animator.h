#pragma once
#include "ecm.h"
#include "cmp_sprite.h"
#include <SFML/Graphics/Sprite.hpp>
#include <utility>
#include <vector>

struct Frame {
    sf::IntRect rect;
    float duration{};
};

struct Animation {
    std::shared_ptr<sf::Texture> texture;
    std::vector<Frame> frames;

    Animation(std::shared_ptr<sf::Texture> t, std::vector<Frame> f) {
        texture = std::move(t);
        frames = std::move(f);
    }
};

class AnimatorComponent : public Component {
private:
    std::vector<Frame> frames;
    float totalLength;
    float totalProgress;
    int frameCount;
    int row;
    std::shared_ptr<SpriteComponent> _spriteComp;

public:
    AnimatorComponent() = delete;
    explicit AnimatorComponent(Entity* parent);

    void update(double dt) override;
    void render() override;
    void setAnimation(Animation& animation);

    void stop();
};
