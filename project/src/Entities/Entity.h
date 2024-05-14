#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

namespace Entities {

class Entity {
private:
    std::unique_ptr<sf::Shape> shape;
    sf::FloatRect bounds;

public:
    Entity(sf::Vector2f pos, std::unique_ptr<sf::Shape> shape);
    void draw(sf::RenderWindow& w) const;
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    void setBounds();
    virtual void setTexture(const sf::Texture& texture) {}
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    virtual bool contains(const sf::Vector2f& point) const;
    
};

}

#endif
