#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button {
private:
    sf::Sprite _sprite;

    bool canClick = true;

public:
    Button(sf::Vector2f pos, const sf::Texture& texture);
    Button() { }; // default constructor
    ~Button() = default;

    bool contains(sf::Vector2f pos);
    bool clickable();
    void click();

    void setColor(sf::Color color);
    void setScale(float x, float y);

    void draw(sf::RenderWindow* window) const;

    void update();

};