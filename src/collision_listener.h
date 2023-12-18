#pragma once
#include <Box2D/Box2D.h>
#include <functional>
#include <unordered_map>

class Box2DContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    // Additional methods if needed
};
