#include <spdlog/spdlog.h>
#include "RangeScreen.h"
#include "Entities/CircleTarget.h"
#include "Spawners/Spawner.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


namespace Screens {

RangeScreen::RangeScreen(sf::RenderWindow* window, Spawners::Spawner* spawner)
: window(window)
, spawner(spawner)
{}

void RangeScreen::init() {
    spawner->init(5);
}

void RangeScreen::draw() const {
    window->clear(sf::Color(120,56,94));

    spawner->draw(window);
 
}

void RangeScreen::handleEvents(sf::Event event) {
    auto* targets = spawner->getTargets();
    switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::MouseButtonPressed:
            //TODO: use Quadtrees instead of a vector to store entities
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                //Convert to float vector
                sf::Vector2f mousePosf(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                auto it = targets->begin();
                while (it != targets->end()) {
                    if ((*it)->contains(mousePosf)) {
                        std::cout << "inside" << std::endl;
                        it = targets->erase(it);  // Remove element and advance iterator
                    } else {
                        ++it;  // Only advance iterator if no erase happened
                    }
                }
            }
            break;
        default:
            break;
    }
}

void RangeScreen::update() {
    spawner->update();
}
    
}