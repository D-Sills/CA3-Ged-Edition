#pragma once
#include <ecm.h>
#include <Box2D/Box2D.h>

enum class Direction { Up, Down, Left, Right };

class CharacterControllerComponent : public Component {
private:
    float _speed{};
    Direction _direction;
    b2Body* _body;
    b2Vec2 _moveDirection;

public:
    void move(const sf::Vector2f& p);

    explicit CharacterControllerComponent(Entity* p,  b2Body *body);
    CharacterControllerComponent() = delete;

	void setSpeed(float speed);

    void update(double dt) override;

    void render() override {}

    bool isMoving() const {
        return _moveDirection.LengthSquared() > 0;
    }
};