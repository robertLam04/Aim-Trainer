#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include "HitBox.h"

namespace Entities {

class CircleTarget;

class HitBox {
private:
    CircleTarget& target;
public:
    HitBox(CircleTarget& target);
    bool contains(const sf::Vector2f& position) const;
};

}

#endif