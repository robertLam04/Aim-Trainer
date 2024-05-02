#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entities/CircleTarget.h"
#include "Entities/HitBox.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    //Load texture from file
    sf::Texture texture;
    if (!texture.loadFromFile("/home/rjlam55/Aim-Trainer/project/target_image.png")) {
        // Error handling: texture failed to load
        return 1; // Exit with error code
    }

    sf::Vector2f pos(400.0f, 300.0f);
    Entities::CircleTarget target(pos, texture, 60.0f);
    Entities::HitBox hitbox(&target);
    hitbox.printBounds();
    
    // Main loop
    while (window.isOpen()) {

        sf::Event event;
        sf::Keyboard keyboard;
        //Close the window if the close button is clicked
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    //Convert to float vector
                    sf::Vector2f mousePosf(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    if (hitbox.hit(mousePosf)) {
                        std::cout << "inside" << std::endl;
                    }
                }
            }
        }

        //Clear the window (once per frame)
        window.clear();

        target.draw(window);

        // Display the window
        window.display();

    }
    
    return 0;
}

