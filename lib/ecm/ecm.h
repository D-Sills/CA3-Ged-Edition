#pragma once
#include <maths.h>
#include <algorithm>
#include <memory>
#include <set>
#include <typeindex>
#include <vector>
#include <functional>

class Entity;
class Scene;

class Component {
	friend Entity;

    class CollisionComponent;
        friend Entity;

protected:
    bool _fordeletion; // should be removed
	explicit Component(Entity* const p);

public:
	Component() = delete;

	bool is_fordeletion() const;

	virtual void update(double dt) = 0;

	virtual void render() = 0;

	virtual ~Component();

    Entity* const _parent;
};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
	std::vector<std::shared_ptr<Entity>> find(const std::string& tag) const;
	std::vector<std::shared_ptr<Entity>>
		find(const std::vector<std::string>& tags) const;

	void addEntity(std::shared_ptr<Entity> entity);
};

class Entity {
	friend struct EntityManager;

private:
    std::function<void(Entity*)> _onCollision;

protected:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;
	float _rotation;
	bool _alive;       // should be updated
	bool _visible;     // should be rendered
	bool _fordeletion; // should be deleted
	std::set<std::string> _tags;


public:
	void addTag(const std::string& t);
	const std::set<std::string>& getTags() const;
    bool hasTag(const std::string& t) const;
	Scene* const scene;
	Entity(Scene* const s);
	Entity(const Entity& ent);
	virtual ~Entity();



	virtual void update(double dt);

	virtual void render();

    // oncollision is set from the collision component
    void setOnCollision(std::function<void(Entity*)> func);
    void onCollision(Entity *other) const;

	//
	const sf::Vector2f& getPosition() const;

	void setPosition(const sf::Vector2f& _position);

	bool is_fordeletion() const;

	float getRotation() const;

	void setRotation(float _rotation);

	bool isAlive() const;

	void setAlive(bool _alive);

	void setForDelete();

	bool isVisible() const;

	void setVisible(bool _visible);

	std::vector<std::shared_ptr<Component>> getComponents();

    void removeComponents();
	void setComponents(std::vector<std::shared_ptr<Component>> components);

	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
        std::shared_ptr<T> ret = std::make_shared<T>(this, params...);
        _components.push_back(ret);
        return ret;
	}

    template <typename T>
    std::shared_ptr<T> getComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T != component");
        for (const auto& c : _components) {
            if (typeid(*c) == typeid(T)) {
                return std::dynamic_pointer_cast<T>(c);
            }
        }
        return nullptr;
    }

	template <typename T>
	std::vector<std::shared_ptr<T>> get_components() const {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (const auto& c : _components) {
			if (typeid(*c) == typeid(T)) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return std::move(ret);
	}

	// Will return a T component, or anything derived from a T component.
	template <typename T>
	std::vector<std::shared_ptr<T>> GetCompatibleComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (auto c : _components) {
			auto dd = dynamic_cast<T*>(&(*c));
			if (dd) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return ret;
	}

    void shared_from_this() const;
};
