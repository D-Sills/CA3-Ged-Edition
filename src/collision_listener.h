#pragma once
#ifndef COLLISION_LISTENER_H
#define COLLISION_LISTENER_H

#include <Box2D/Box2D.h>
#include <functional>
#include <unordered_map>
#include <ecm.h>
#include <memory>

class Box2DContactListener : public b2ContactListener {
    void BeginContact(b2Contact *contact) override {
        // Retrieve the entities involved in the contact
        auto* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        auto* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

        if (bodyUserDataA && bodyUserDataB) {
            auto* entityA = static_cast<Entity*>(bodyUserDataA);
            auto* entityB = static_cast<Entity*>(bodyUserDataB);

            entityA->onCollision(entityB);
            entityB->onCollision(entityA);
        }
    }


    void EndContact(b2Contact* contact) override {
        // Retrieve the entities involved in the contact


    }
};

#endif //COLLISION_LISTENER_H