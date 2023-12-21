#pragma once
#include <ecm.h>
#include <Box2D/Box2D.h>
#include <memory>

class ColliderComponent : public Component {
public:
    ColliderComponent(Entity* parent, const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);

    void update(double dt) override {}
    void render() override {}

    void onCollisionEnter(const std::shared_ptr<Entity>& e);

private:

};
