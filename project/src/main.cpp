/*
TODO:
    - Scoring system
    - Crosshair
        - Implement customizability in settings screen
    - Implement some physics spawner?

BUGs:

*/

#include "Logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Entities/CircleTarget.h"
#include "Screens/GameScreen.h"
#include "Screens/MenuScreen.h"
#include "Spawners/Spawner.h"
#include "ScreenManager.h"
#include "GameData.h"

int main() {

    //console->set_level(spdlog::level::debug);

    GameDataRef data = std::make_shared<GameData>();

    std::unique_ptr<Screens::Screen> initialScreen = std::make_unique<Screens::MenuScreen>(data);
    ScreenManager screenManager(std::move(initialScreen));

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
    


