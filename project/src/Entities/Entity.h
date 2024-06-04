#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Velocity.h"

namespace Entities {

class Entity {
public:
    virtual ~Entity() = default;

    virtual void draw(sf::RenderWindow& w) const = 0;
    virtual void setPosition(sf::Vector2f pos) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setVelocity(float x, float y) = 0;
    virtual void setTexture(const sf::Texture& texture) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual Velocity getVelocity() const = 0;
    virtual bool contains(const sf::Vector2f& point) const = 0;
    virtual void update(float time) = 0;
    virtual std::vector<sf::Vector2f> getKeyPoints() const = 0;  // New method
};

}

#endif
