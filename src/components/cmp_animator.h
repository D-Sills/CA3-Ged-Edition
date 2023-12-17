#pragma once
#include "ecm.h"
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

struct Frame {
    sf::IntRect rect;
    float duration;
};

class AnimatorComponent : public Component {
protected:
    std::vector<Frame> frames;
    float totalLength;
    float totalProgress;
    int frameCount;
    int row;

public:
    AnimatorComponent() = delete;
    explicit AnimatorComponent(Entity* parent);

    void update(double dt) override;
    void render() override;
    void addFrame(const Frame& frame);
    void setAnimation(const std::shared_ptr<sf::Texture>& texture, const std::vector<Frame>& frames);
    void setRow(int row);
    int getRow() const;
};
