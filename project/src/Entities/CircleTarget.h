#ifndef CIRCLE_TARGET_H
#define CIRCLE_TARGET_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "HitBox.h"

namespace Entities {

class CircleTarget : public Entity {
private:

    sf::CircleShape _circle;
    HitBox _hitbox;

public: 
    CircleTarget(sf::CircleShape circle,sf::Vector2f pos);
    bool contains(const sf::Vector2f& point) const override;
    float getRadius() const;

};

}

#endif 