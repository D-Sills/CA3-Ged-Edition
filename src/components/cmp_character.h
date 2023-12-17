#include <memory>
#include <SFML/Graphics.hpp>
#include "cmp_character_controller.h"
#include "cmp_sprite.h"

using namespace std;
using namespace sf;

class CharacterComponent : public Component {
protected:
    int _health;
    int _damage;
    float _attackTime;
    float _deathTime;

public:
    explicit CharacterComponent(Entity* p);
    ~CharacterComponent() override = default;

    void setHealth(int health);
    void setDamage(int damage);
    int getHealth() const;
    int getDamage() const;

    Entity *_parent;
};
