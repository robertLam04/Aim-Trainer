#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

namespace Entities {

class HitBox {
private:
    sf::FloatRect bounds;
public:
    HitBox(Entity* entity);
    void setHitbox(Entity* entity);
    bool hit(sf::Vector2f position) const;
    void printBounds();
};

}

#endif