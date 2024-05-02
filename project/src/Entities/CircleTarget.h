#ifndef CIRCLE_TARGET_H
#define CIRCLE_TARGET_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

namespace Entities {
class CircleTarget : public Entity {
public: 
    CircleTarget(sf::Vector2f pos, sf::Texture& texture, float radius);
};

}

#endif 