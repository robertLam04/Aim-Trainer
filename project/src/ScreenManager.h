#pragma once

#include "Screens/Screen.h"
#include <map>
#include <memory>
#include <string>

class ScreenManager {
private:
    std::map<std::string, std::unique_ptr<Screens::Screen>> screens;
    std::unique_ptr<Screens::Screen> currentScreen;

public:
    ScreenManager(std::unique_ptr<Screens::Screen> start_screen);
    ~ScreenManager() = default;

    void handleEvents(sf::Event event);
    void update();
    void draw() const;
    
};