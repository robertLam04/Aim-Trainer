#include<SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

namespace Entities {

    Entity::Entity(sf::Vector2f pos, std::unique_ptr<sf::Shape> shape)
    : shape(std::move(shape))
    {
        setPosition(pos);
    }

    void Entity::draw(sf::RenderWindow& w) const {
        w.draw(*shape);
    }

    void Entity::setPosition(sf::Vector2f pos) {
        shape->setPosition(pos);
    }

    void Entity::setPosition(float x, float y) {
        shape->setPosition(x, y);
    }

    sf::Vector2f Entity::getPosition() const {
        return shape->getPosition();
    }

    sf::FloatRect Entity::getBounds() const {
        return shape->getGlobalBounds();
    }

    //Defualt implementation for entities without a hitbox
    bool Entity::contains(const sf::Vector2f& point) const {
        return false;
    }

} // namespace Entities