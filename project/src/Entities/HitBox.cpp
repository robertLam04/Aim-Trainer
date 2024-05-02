#include <SFML/Graphics.hpp>
#include "HitBox.h"
#include <iostream>

namespace Entities {

HitBox::HitBox(Entity* entity) {
    bounds = entity->getGlobalBounds();
}

void HitBox::setHitbox(Entity* entity) {
    bounds = entity->getGlobalBounds();
}

bool HitBox::hit(sf::Vector2f pos) const {
    return bounds.contains(pos);
}

void HitBox::printBounds() {
    // Print the bounds of the HitBox
    std::cout << "Bounds of HitBox:" << std::endl;
    std::cout << "Left: " << bounds.left << std::endl;
    std::cout << "Top: " << bounds.top << std::endl;
    std::cout << "Width: " << bounds.width << std::endl;
    std::cout << "Height: " << bounds.height << std::endl;
}

}