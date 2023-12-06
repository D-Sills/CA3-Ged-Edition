#include <memory>
#include <SFML/Graphics.hpp>
#include "cmp_actor_movement.h"
#include "cmp_sprite.h"

using namespace std;
using namespace sf;

class cmp_character {
protected:
    int _health;
    int _damage;
    float _speed;
    float _attackTime;
    float _deathTime;
    std::shared_ptr<sf::Texture> _texture;
    shared_ptr<ActorMovementComponent> _movement;
    shared_ptr<SpriteComponent> _sprite;

public:
    cmp_character() = delete;
    explicit cmp_character(Entity* p);

    virtual void update(double dt) = 0;
    virtual void render() = 0;
    ~cmp_character() = default;

    void set_health(int health);
    int get_health() const;

    void set_damage(int damage);

    float get_speed() const;
    void set_speed(float speed);

    virtual void attack(double dt) = 0;

    Entity *_parent;
};
