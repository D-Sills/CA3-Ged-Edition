#include "system_physics.h"
#include "Box2D/Box2D.h"
using namespace std;
using namespace sf;

namespace Physics {
	static shared_ptr<b2World> world;
	const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    Box2DContactListener contactListenerInstance;
    std::vector<b2Body*> destructionQueue;

	void initialise() {
		b2Vec2 gravity(0.0f, 0.0f);
		world.reset(new b2World(gravity));
        world->SetContactListener(&contactListenerInstance);
	}

	void shutdown() { world.reset(); }

	void update(const double& dt) {
        world->Step((float)dt, velocityIterations, positionIterations);
	}

	std::shared_ptr<b2World> GetWorld() { return world; }

    void markBodyForDestruction(b2Body* body) {
        destructionQueue.push_back(body);
    }

    void processDestructionQueue() {
        for (auto& body : destructionQueue) {
            if (body) {
                world->DestroyBody(body);
                body = nullptr;
            }
        }
        destructionQueue.clear();
    }

	const Vector2f bv2_to_sv2(const b2Vec2& in, bool scale) {
		if (scale) {
			return Vector2f((in.x * physics_scale), (in.y * physics_scale));
		}
		else {
			return Vector2f(in.x, in.y);
		}
	}

	const b2Vec2 sv2_to_bv2(const Vector2f& in, bool scale) {
		if (scale) {
			return b2Vec2((in.x * physics_scale_inv), (in.y * physics_scale_inv));
		}
		else {
			return b2Vec2(in.x, in.y);
		}
	}

	const Vector2f invert_height(const Vector2f& in) {
		return Vector2f(in.x, 720 - in.y);
	}
} // namespace Physics