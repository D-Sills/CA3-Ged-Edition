#include "cmp_button.h"
#include "AudioManager.h"
#include "../../engine/system_resources.h"
#include "SFML/Window/Mouse.hpp"
#include "../../engine/engine.h"

using namespace sf;
using namespace std;

Button::Button(Entity* parent, const sf::Vector2f& position, const std::string& txt,
               const sf::Color& idleCol, const sf::Color& hoverCol, const sf::Color& activeCol)
        : Component(parent), idleColor(idleCol), hoverColor(hoverCol), activeColor(activeCol),
          buttonState(ButtonState::Idle), isHoveredFirstTime(true) {

    auto& font = *Resources::get<Font>("font.ttf");
    text.setFont(font);
    text.setString(txt);
    text.setFillColor(Color::Black);
    text.setCharacterSize(20);
    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2, bounds.height / 2);

    shape.setSize(Vector2f(200, 70));
    shape.setFillColor(idleColor);
    shape.setOrigin(100, 35); // Center origin based on size
    shape.setPosition(position);

    text.setPosition(shape.getPosition());
}

void Button::update(double dt) {
    Vector2f mousePos = Mouse::getPosition(Engine::GetWindow());
    auto state = Mouse::isButtonPressed(Mouse::Left) ? ButtonState::Down : ButtonState::Idle;

    if (shape.getGlobalBounds().contains(mousePos)) {
        state = (state == ButtonState::Idle) ? ButtonState::Hover : state;

        if (state == ButtonState::Hover && isHoveredFirstTime) {
            AudioManager::get_instance().playSoundEffect("buttonHover");
            isHoveredFirstTime = false;
        }
    } else {
        isHoveredFirstTime = true;
    }

    switch (state) {
        case ButtonState::Idle:
            shape.setFillColor(idleColor);
            break;
        case ButtonState::Hover:
            shape.setFillColor(hoverColor);
            break;
        case ButtonState::Active:
            shape.setFillColor(activeColor);
            break;
        case ButtonState::Down:
            if (buttonState != ButtonState::Down) {
                AudioManager::get_instance().playSoundEffect("buttonClick");
            }
            shape.setFillColor(activeColor);
            break;
    }

    buttonState = state;
}

void Button::render() {
    Renderer::queue(&shape);
    Renderer::queue(&text);
}

bool Button::isPressed() const {
    return buttonState == ButtonState::Active;
}
