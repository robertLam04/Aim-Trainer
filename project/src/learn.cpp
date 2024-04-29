#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::CircleShape circle(100);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(400, 300);

    // Main loop
    while (window.isOpen()) {

        sf::Event event;
        sf::Keyboard keyboard;
        //Close the window if the close button is clicked
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (keyboard.isKeyPressed(sf::Keyboard::Left)) {
                circle.move(-5,0);
            }
            if (keyboard.isKeyPressed(sf::Keyboard::Right)) {
                circle.move(5,0);
            }
        }

        //Clear the window (once per frame)
        window.clear();

        window.draw(circle);

        // Display the window
        window.display();

    }
    
    return 0;
}

