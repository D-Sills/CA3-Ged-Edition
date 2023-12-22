#include "cmp_button.h"

#include <utility>
#include "../../engine/system_resources.h"
#include "SFML/Window/Mouse.hpp"
#include "../../engine/engine.h"
#include "../../audio_manager.h"
#include "../../engine/system_renderer.h"

using namespace sf;
using namespace std;

Button::Button(Entity* parent, const sf::Vector2f& position, const std::string& txt,
               const sf::Color& idleCol, const sf::Color& hoverCol, const sf::Color& activeCol, bool hasTexture, std::function<void()> onClickFunc)
        : Component(parent), idleColor(idleCol), hoverColor(hoverCol), activeColor(activeCol),
          buttonState(ButtonState::Idle), isHoveredFirstTime(true), onClickFunc(std::move(onClickFunc)) {

    auto& font = *Resources::get<Font>("font.ttf");
    text.setFont(font);
    text.setString(txt);
    text.setFillColor(Color::Black);
    text.setCharacterSize(20);
    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2, bounds.height / 2);

    if (hasTexture) {
        auto& texture = *Resources::load<Texture>("button_texture.png");
        shape.setTexture(&texture);
        shape.setSize(static_cast<sf::Vector2f>(texture.getSize()));
        shape.setOrigin(shape.getSize() / 2.0f);
    } else {
        shape.setSize(Vector2f(200, 70));
        shape.setOrigin(shape.getSize() / 2.0f);
    }
    shape.setPosition(position);

    text.setPosition(shape.getPosition());
}

void Button::update(double dt) {
    auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));

    if (shape.getGlobalBounds().contains(mousePos)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (buttonState != ButtonState::Down) {
                AudioManager::get_instance().playSound("click");
                if (onClickFunc) {
                    onClickFunc(); // Execute the callback
                }
                shape.setFillColor(activeColor);
            }
            buttonState = ButtonState::Down;
        } else {
            if (isHoveredFirstTime) {
                AudioManager::get_instance().playSound("hover");
                isHoveredFirstTime = false;
                shape.setFillColor(hoverColor);
            }
            buttonState = ButtonState::Hover;
        }
    } else {
        if (buttonState != ButtonState::Idle) {
            shape.setFillColor(idleColor);
        }
        buttonState = ButtonState::Idle;
        isHoveredFirstTime = true;
    }
}

void Button::render() {
    Renderer::queue(&shape);
    Renderer::queue(&text);
}