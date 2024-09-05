/*
TODO:
    - Scoring system
    - Crosshair
        - Implement customizability in settings screen
    - Implement some physics spawner?
    - Target Collision
        - Quad trees?
        - rectangular hitbox estimation (for complex shapes)?

BUGs:

*/

#include "Logger.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
#include "GameData.h"
#include "ScreenState.h"

/*int main() {
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Window");

    auto screenManager = new ScreenManagerTest(ScreenState::MainMenu, &window);

    while (window.isOpen()) {
        sf::Event event;
        sf::Keyboard keyboard;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        screenManager->draw();

        window.display();
    }

    delete screenManager;

    return 0;
}*/


int main() {

    //console->set_level(spdlog::level::debug);

    GameDataRef data = std::make_shared<GameData>();
    Settings settings;

    ScreenManager screenManager(ScreenState::MainMenu, data, settings);

    console->info("Window size: width = {}, height = {}", data->window.getSize().x, data->window.getSize().y);

    // Main loop
    while (data->window.isOpen()) {
        sf::Event event;
        sf::Keyboard keyboard;
       
        while (data->window.pollEvent(event)) {
            screenManager.handleEvents(event);
        }

        //Clear the window (once per frame)
        data->window.clear();

        screenManager.update();

        screenManager.draw();

        // Display the window
        data->window.display();

    }

    return 0;
    
}








    


