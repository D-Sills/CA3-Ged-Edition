#pragma once
#include <ecm.h>

enum class Direction { Up, Down, Left, Right };

class CharacterControllerComponent : public Component {
private:
    float _speed;
    Direction _direction;

public:
    static bool validMove(const sf::Vector2f&);
    void move(const sf::Vector2f& p);
    void move(Direction dir);

    CharacterControllerComponent(Entity* p, float speed);
    CharacterControllerComponent() = delete;

	float getSpeed() const;
	void setSpeed(float speed);

	Direction getDirection();
	void setDirection(Direction direction);

    Entity *_parent;
};