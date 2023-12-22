#include "ecm.h"

using namespace std;

Entity::Entity(Scene* const s)
	: _position({ 0, 0 }), _rotation(0), _alive(true), _visible(true),
	scene(s), _fordeletion(false) {}

// Copy constructor
Entity::Entity(const Entity& ent) : _position(ent._position), _rotation(ent._rotation), _alive(ent._alive), _visible(ent._visible),
_fordeletion(ent._fordeletion), scene(ent.scene)
{
	_components = ent._components;
}

void Entity::addTag(const std::string& t) { _tags.insert(t); }
const std::set<std::string>& Entity::getTags() const { return _tags; }

void Entity::update(double dt) {
	if (!_alive) {
		_visible = false;
		return;
	}
	for (size_t i = 0; i < _components.size(); i++) {
		if (_components[i]->is_fordeletion()) {
            _components.erase(_components.begin() + i);
            --i;
            continue;
        }
		_components[i]->update(dt);
	}
}

bool Entity::is_fordeletion() const { return _fordeletion; }

void Entity::render() {
	if (!_visible) {
		return;
	}
	for (auto& c : _components) {
		c->render();
	}
}

const sf::Vector2f& Entity::getPosition() const { return _position; }

void Entity::setPosition(const sf::Vector2f& _position) {
	Entity::_position = _position;
}

float Entity::getRotation() const { return _rotation; }

std::vector<std::shared_ptr<Component>> Entity::getComponents() { return _components; }

void Entity::setComponents(std::vector<std::shared_ptr<Component>> components)
{
	_components = components;
}

void Entity::setRotation(float _rotation) { Entity::_rotation = _rotation; }

bool Entity::isAlive() const { return _alive; }

void Entity::setAlive(bool _alive) { Entity::_alive = _alive; }

void Entity::setForDelete() {
	_fordeletion = true;
	_alive = false;
	_visible = false;
}

bool Entity::hasTag(const std::string& t) const {
    return _tags.find(t) != _tags.end();
}

bool Entity::isVisible() const { return _visible; }

void Entity::setVisible(bool _visible) { Entity::_visible = _visible; }

Component::Component(Entity* const p) : _parent(p), _fordeletion(false) {}

Entity::~Entity() {
	_components.clear();
}

void Entity::removeComponents() {
    // delete all components
    _components.clear();
}

void Entity::setOnCollision(std::function<void(Entity*)> func) {
    _onCollision = std::move(func);
}

void Entity::onCollision(Entity* other) const {
    if (_onCollision) {
        _onCollision(other);
    }
}

Component::~Component() = default;

bool Component::is_fordeletion() const { return _fordeletion; }

void EntityManager::update(double dt) {
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i]->is_fordeletion()) {
            //print the tag of the entity that is being deleted
            std::cout << "Entity with tag: " << list[i]->getTags().begin()->c_str() << " is being deleted" << std::endl;

			list.erase(list.begin() + i);
			--i;
			continue;
		}
		if (list[i]->_alive) {
			list[i]->update(dt);
		}
	}
}

void EntityManager::render() {
	for (auto& e : list) {
		if (e->_visible) {
			e->render();
		}
	}
}

void EntityManager::addEntity(shared_ptr<Entity> entity) { list.push_back(entity); }

vector<shared_ptr<Entity>> EntityManager::find(const string& tag) const {
	vector<shared_ptr<Entity>> ret;
	for (auto& e : list) {
		const auto tgs = e->_tags;
		if (tgs.find(tag) != tgs.end()) {
			ret.push_back(e);
		}
	}
	return ret;
}

vector<shared_ptr<Entity>>
EntityManager::find(const vector<string>& tags) const {
	vector<shared_ptr<Entity>> ret;
	for (auto& e : list) {
		const auto tgs = e->_tags;
		if (any_of(tags.begin(), tags.end(),
			[&tgs](auto t) { return tgs.find(t) != tgs.end(); })) {
			ret.push_back(e);
		}
	}
	return ret;
}