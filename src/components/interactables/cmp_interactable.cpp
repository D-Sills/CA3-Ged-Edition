#include "cmp_interactable.h"

InteractableComponent::InteractableComponent(Entity* p)
        : Component(p) {}

void InteractableComponent::update(double dt) {
    // Update logic for the interactable, if any
}

void InteractableComponent::render() {
    // Render logic for the interactable, if any
}

void InteractableComponent::interact() {
    // Default interaction logic
}

sf::FloatRect InteractableComponent::getBounds() const {

    return {};
}
