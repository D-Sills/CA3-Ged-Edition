#include "cmp_animator.h"
#include "cmp_sprite.h"

using namespace sf;
using namespace std;

AnimatorComponent::AnimatorComponent(Entity* p)
        : Component(p), frameCount(0), row(0), totalProgress(0.f), totalLength(0.f) {
    _spriteComp = _parent->GetCompatibleComponent<SpriteComponent>()[0];
}

void AnimatorComponent::setAnimation(Animation& animation) {
    // Check if the SpriteComponent exists or create a new one
    if (!_spriteComp) {
        _parent->addComponent<SpriteComponent>();
        _spriteComp = _parent->GetCompatibleComponent<SpriteComponent>()[0];
    }

    // Ensure the sprite component has the correct texture set
    _spriteComp->setTexture(animation.texture);

    // Update the frames and reset counters
    frames = animation.frames;
    frameCount = 0;
    totalLength = 0.f;
    for (const auto& f : frames) {
        totalLength += f.duration;
    }

    // Set the texture rect of the first frame
    if (!frames.empty()) {
        _spriteComp->setTextureRect(frames[0].rect);
    }
}

void AnimatorComponent::stop() {
    frames.clear();
    frameCount = 0;
    totalLength = 0.f;
    totalProgress = 0.f;

}

void AnimatorComponent::update(double dt) {
    if (frames.empty()) return;

    totalProgress += dt;
    if (totalProgress >= frames[frameCount].duration) {
        frameCount = (frameCount + 1) % frames.size();
        _spriteComp->setTextureRect(frames[frameCount].rect);
        totalProgress = 0.f;
    }
}



void AnimatorComponent::render() {}
