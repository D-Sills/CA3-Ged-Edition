#pragma once

#include "ecm.h"
#include "../components/cmp_sprite.h"
#include "../components/ui/cmp_text.h"


class Pause : public Component {
public:
    Pause() = delete;
    explicit Pause(Entity* p);
    void update(double dt) override;
    void render() override;

private:
    std::shared_ptr<SpriteComponent> _background;
    std::shared_ptr<TextComponent> _text;

};


