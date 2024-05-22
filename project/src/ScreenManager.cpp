#include "ScreenManager.h"
#include <memory>

ScreenManager::ScreenManager(std::unique_ptr<Screens::Screen> initialScreen)
    : currentScreen(std::move(initialScreen)) {
    currentScreen->init();
}

void ScreenManager::handleEvents(sf::Event event) {
    if (currentScreen) {
        currentScreen->handleEvents(event);
    }
}

void ScreenManager::update() {
    if (currentScreen) {
        currentScreen->update();
        auto nextScreen = currentScreen->getNextScreen();
        if (nextScreen.has_value()) {
            currentScreen = std::move(nextScreen.value());
            currentScreen->init();
        }
    }
}

void ScreenManager::draw() const {
    if (currentScreen) {
        currentScreen->draw();
    }
}
