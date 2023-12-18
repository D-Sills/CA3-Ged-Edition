
#include "../components/cmp_character.h"
#include "../components/cmp_animator.h"
#include "../components/cmp_projectile_emitter.h"
#include "../components/cmp_collider.h"

class Player {
private:
    std::shared_ptr<sf::Texture> _idle;
    std::shared_ptr<sf::Texture> _run;

    std::shared_ptr<CharacterComponent> _character;
    std::shared_ptr<CharacterControllerComponent> _controller;
    std::shared_ptr<AnimatorComponent> _animator;
    std::shared_ptr<SpriteComponent> _spriteComp;
    std::shared_ptr<ProjectileEmitterComponent> _projectileEmitter;
    std::shared_ptr<ColliderComponent> _collider;

    shared_ptr<Entity> _player;
public:
    Player(Scene *const s, sf::Vector2f position);

    void update(double dt);
    void render();

    Entity* getEntity() const;
};
