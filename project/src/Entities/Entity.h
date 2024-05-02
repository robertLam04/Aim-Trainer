#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

namespace Entities {

class Entity {
private:
    sf::Shape* shape;
    sf::Vector2f pos; 
    sf::FloatRect bounds;
public:
    Entity(sf::Vector2f pos, sf::Shape* shape);
    void draw(sf::RenderWindow& w);
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    void setBounds();
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds();
    sf::Shape* getShape();
    virtual ~Entity() = default;
};

}

#endif
