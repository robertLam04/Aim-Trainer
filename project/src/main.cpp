/*
Technical debt: 
    - Try to avoid using pointers over references
    - Need to be iterable and deleteable 
    - Notion of smart pointers
*/

#include "Logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Entities/CircleTarget.h"
#include "Screens/RangeScreen.h"
#include "Spawners/Spawner.h"

int main() {

    console->set_level(spdlog::level::info);
    
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    //Load texture from file
    sf::Texture texture;
    console->debug("Loading texture");
    if (!texture.loadFromFile("/home/rjlam55/Aim-Trainer/project/target_image.png")) {
        // Error handling: texture failed to load
        return 1; // Exit with error code
    }

    //Create the target(s)
    //TODO: Make pure virtual method hitbox in entity
    //then use Entity as static type

    //Setup screen
    console->debug("Creating a spawner");
    Spawners::Spawner* spawner = new Spawners::Spawner(texture);
    console->debug("Creating range screen");
    Screens::Screen* screen = new Screens::RangeScreen(&window, spawner);

    console->debug("Initializing Screen");
    screen->init();
    
    // Main loop
    while (window.isOpen()) {
        console->debug("Main Loop");
        sf::Event event;
        sf::Keyboard keyboard;
       
        while (window.pollEvent(event)) {
            console->debug("Polling Event");
            screen->handleEvents(event);
        }

        //Clear the window (once per frame)
        window.clear();

        screen->update();

        console->debug("Drawing screen");
        screen->draw();

        console->debug("Displaying screen");
        // Display the window
        window.display();

    }
    
    delete screen;

    return 0;

}

