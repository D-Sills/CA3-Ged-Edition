#pragma once
#include <ecm.h>

enum class Direction { Up, Down, Left, Right };

class CharacterControllerComponent : public Component {
private:
    float _speed;
    Direction _direction;
    bool isMoving = false;

public:
    static bool validMove(const sf::Vector2f&);
    void move(const sf::Vector2f& p);
    void move(Direction dir);

    explicit CharacterControllerComponent(Entity* p);
    CharacterControllerComponent() = delete;

	float getSpeed() const;
	void setSpeed(float speed);

	Direction getDirection();
	void setDirection(Direction direction);

    void update(double dt) override;
    void render() override;

    Entity *_parent;

    bool getIsMoving();
};