#include "collision_listener.h"
#include "ecm.h"

void Box2DContactListener::BeginContact(b2Contact* contact) {
    // Retrieve the entities involved in the contact
    auto* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyUserDataA && bodyUserDataB) {
        auto* entityA = static_cast<Entity*>(bodyUserDataA);
        auto* entityB = static_cast<Entity*>(bodyUserDataB);

        // Trigger collision events
        entityA->onCollision(entityB);
        entityB->onCollision(entityA);
    }
}

void Box2DContactListener::EndContact(b2Contact* contact) {
    // Handle end of contact if necessary
}
