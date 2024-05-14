#include <SFML/Graphics.hpp>

#include <iostream>
#include "CircleTarget.h"
#include "Entity.h"
#include "HitBox.h"

namespace Entities {
    CircleTarget::CircleTarget(sf::CircleShape circle, sf::Texture& texture, sf::Vector2f pos)
        : Entity(pos, std::make_unique<sf::CircleShape>(circle))
        , _circle(circle)
        , _hitbox(*this)
    {}

    /*CircleTarget::CircleTarget(float radius, sf::Texture& texture, sf::Vector2f pos)
        : Entity(pos, &circle)
        , circle(radius)
        , circle_ref(&circle)
        , hitbox(this)
    {
        std::cout << "CircleTarget constructor called\n";
        circle_ref->setTexture(&texture);
        circle_ref->setOrigin(radius, radius);
    }
    
    This does not work because initializer list is not always executed in order
    Entity constructor must be called before derived class members are intialized
    
    */

    void CircleTarget::setTexture(const sf::Texture& texture) {
        _circle.setTexture(&texture);
    }

    bool CircleTarget::contains(const sf::Vector2f& point) const {
        return _hitbox.contains(point);
    }

    float CircleTarget::getRadius() const {
        return _circle.getRadius();
    }


} // namespace Entities

