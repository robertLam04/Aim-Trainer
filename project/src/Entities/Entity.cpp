#include<SFML/Graphics.hpp>
#include "Entity.h"

namespace Entities {

    Entity::Entity(sf::Vector2f pos, sf::Shape* shape_ref)
    : pos(pos) 
    , shape(shape_ref)
    {
        setPosition(pos);
        setBounds();
    }

    void Entity::draw(sf::RenderWindow& w) {
        w.draw(*shape);
    }

    void Entity::setPosition(sf::Vector2f pos) {
        this->pos = pos;
        shape->setPosition(pos);
    }

    void Entity::setPosition(float x, float y) {
        pos.x = x;
        pos.y = y;
        shape->setPosition(pos);
    }

    void Entity::setBounds() {
        bounds = shape->getGlobalBounds();
    }

    sf::Vector2f Entity::getPosition() const {
        return pos;
    }

    sf::FloatRect Entity::getGlobalBounds() {
        return bounds;
    }

    sf::Shape* Entity::getShape() {
        return shape;
    }

} // namespace Entities