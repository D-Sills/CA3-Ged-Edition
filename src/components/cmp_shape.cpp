#include "cmp_shape.h"
#include "../engine/system_renderer.h"

using namespace sf;
using namespace std;

ShapeComponent::ShapeComponent(Entity* p, const sf::Color& color)
        : Component(p), shape(make_shared<CircleShape>()) {
    shape->setFillColor(color);
}

void ShapeComponent::update(double dt) {
    shape->setPosition(_parent->getPosition());
    shape->setRotation(deg2rad(_parent->getRotation()));
}

void ShapeComponent::render() { Renderer::queue(shape.get()); }

Shape& ShapeComponent::getShape() const { return *shape; }

template <typename T, typename... Targs>
void ShapeComponent::setShape(Targs... params) {
    shape.reset(new T(params...));
}
