#pragma once
#include "ecm.h"
#include <Box2D/Box2D.h>
#include <memory>

class ColliderComponent : public Component {
public:
    ColliderComponent(Entity* parent, const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);
    ~ColliderComponent() override;

    void update(double dt) override;
    void render() override {}

    b2Body* getBody() const;
    void onCollisionEnter(std::function<void(Entity*)> callback);

private:
    std::unique_ptr<b2Body, std::function<void(b2Body*)>> _body;
    std::function<void(Entity*)> _onCollisionEnter;
};
