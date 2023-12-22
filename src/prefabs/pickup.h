//
// Created by darrs on 21/12/2023.
//

#ifndef LASTLIGHT_PICKUP_H
#define LASTLIGHT_PICKUP_H

#include "player.h"
#include "ecm.h"

class Pickup : public Component {
private:
    PickupType _type;
    std::function<void()> onPickup;
    std::shared_ptr<SpriteComponent> _sprite;

    b2Body* _body;

public:
    explicit Pickup(Entity* p, PickupType type);
    ~Pickup() override = default;

    void update(double dt) override {}

    void onCollisionEnter(Entity* other);

    void render() override {}

};


#endif //LASTLIGHT_PICKUP_H
