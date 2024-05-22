#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f pos, const sf::Texture& texture)
: _sprite(sf::Sprite(texture))

{
    _sprite.setPosition(pos);
    _sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

bool Button::contains(sf::Vector2f pos) {
    sf::FloatRect bounds = _sprite.getGlobalBounds();

    return bounds.contains(pos);
}

bool Button::clickable() {
    return canClick;
}

void Button::click() {
    if (canClick) {
        /* Click */
        canClick = false;
    }
}

void Button::setScale(float x, float y) {
    _sprite.setScale(x, y);
}

void Button::setColor(sf::Color color) {
    _sprite.setColor(color);
}

void Button::update() {
    canClick = true;
}

void Button::draw(sf::RenderWindow* window) const {
    window->draw(_sprite);
}
