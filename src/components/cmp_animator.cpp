#include "cmp_animator.h"
#include "cmp_sprite.h"

using namespace sf;
using namespace std;

AnimatorComponent::AnimatorComponent(Entity* p)
        : Component(p), frameCount(0), row(0), totalProgress(0.f), totalLength(0.f) {}

void AnimatorComponent::addFrame(const Frame& frame) {
    frames.push_back(frame);
    totalLength += frame.duration;
}

void AnimatorComponent::setAnimation(const shared_ptr<Texture>& texture, const vector<Frame>& newFrames) {
    auto spriteComponents = _parent->GetCompatibleComponent<SpriteComponent>();
    if (!spriteComponents.empty()) {
        spriteComponents[0]->setTextureRect(frames[frameCount].rect);
    } else {
        _parent->addComponent<SpriteComponent>(texture, frames[frameCount].rect);
    }
    frames = newFrames;
    frameCount = 0;
    totalLength = 0.f;
    for (const auto& f : frames) {
        totalLength += f.duration;
    }
}

void AnimatorComponent::setRow(int newRow) {
    row = newRow;
    frameCount = 0;
}

int AnimatorComponent::getRow() const {
    return row;
}

void AnimatorComponent::update(double dt) {
    if (frames.empty()) return;

    totalProgress += dt;
    if (totalProgress >= frames[frameCount].duration) {
        frameCount = (frameCount + 1) % frames.size();
        auto spriteComponents = _parent->GetCompatibleComponent<SpriteComponent>();
        if (!spriteComponents.empty()) {
            spriteComponents[0]->setTextureRect(frames[frameCount].rect);
        }
        totalProgress = 0.f;
    }
}

void AnimatorComponent::render() {}
