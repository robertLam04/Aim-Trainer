#include <SFML/Graphics.hpp>

#include "CircleTarget.h"
#include "Entity.h"

namespace Entities {
    CircleTarget::CircleTarget(sf::Vector2f pos, sf::Texture& texture, float radius)
        : Entity(pos, new sf::CircleShape(radius)) // Initialize the base class Entity
    {
        // Set properties of the circle shape
        sf::CircleShape* circle = static_cast<sf::CircleShape*>(getShape()); // Cast the shape pointer to sf::CircleShape*
        circle->setPosition(pos);
        circle->setTexture(&texture);
    }

} // namespace Entities

