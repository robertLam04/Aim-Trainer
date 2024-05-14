#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "HitBox.h"
#include "CircleTarget.h"

namespace Entities {

HitBox::HitBox(CircleTarget& target)
: target(target)
{}

bool HitBox::contains(const sf::Vector2f& pos) const {
    sf::Vector2f origin = target.getPosition();
    float distance = std::sqrt(std::pow(pos.x - origin.x, 2) + std::pow(pos.y - origin.y, 2));
    // Adjust the hit range according to your specific requirements
    float hitRange = target.getBounds().height / 2;
    return distance <= hitRange;
}

}