#include "ScreenManager.h"
#include "Screens/MenuScreen.h"
#include "Screens/GameScreen.h"
#include "Screens/PauseScreen.h"
#include "Screens/SettingsScreen.h"

ScreenManager::ScreenManager(ScreenState initialState, GameDataRef data, Settings settings)
    : currentState(initialState)
    , _data(data) 
    , settings(settings)
    
{
    console->info("Initializing ScreenManager with initial state: " + std::to_string(static_cast<int>(initialState)));
    pushState(initialState);
}

void ScreenManager::handleEvents(sf::Event event) {
    if (!stateStack.empty()) {
        console->debug("Handling events for current state: " + std::to_string(static_cast<int>(currentState)));
        stateStack.top()->handleEvents(event);
    }
}

void ScreenManager::update() {
    if (!stateStack.empty()) {
        console->debug("Updating current state: " + std::to_string(static_cast<int>(currentState)));
        stateStack.top()->update();
        ScreenState nextState = stateStack.top()->getNextScreen();

        if (nextState != currentState) {
            settings.loadSettings("/home/rjlam55/Aim-Trainer/project/Settings.txt");
            console->info("State transition detected from " + std::to_string(static_cast<int>(currentState)) + " to " + std::to_string(static_cast<int>(nextState)));
            if (nextState == ScreenState::GameResume) {
                while (stateStack.top()->getThisScreen() != ScreenState::Game) {
                    stateStack.pop();
                }
                stateStack.top()->init();
                currentState = ScreenState::Game;
                return;
            }
            console->info("Pushing new state: " + std::to_string(static_cast<int>(nextState)));
            pushState(nextState); // Push the new state
        }
    }
}


void ScreenManager::draw() const {
    if (!stateStack.empty()) {
        console->debug("Drawing current state: " + std::to_string(static_cast<int>(currentState)));
        stateStack.top()->draw();
    }
}

void ScreenManager::pushState(ScreenState newState) {
    if (!stateStack.empty()) {
        stateStack.top()->onExit();
    }
    stateStack.push(std::move(createState(newState)));
    stateStack.top()->init();  // Call init method before entering the new state
    currentState = newState;
}

void ScreenManager::popState() {
    if (!stateStack.empty()) {
        stateStack.top()->onExit();
        stateStack.pop();
    }
}

std::unique_ptr<Screens::Screen> ScreenManager::createState(ScreenState state) {
    console->debug("Creating screen: " + std::to_string(static_cast<int>(state)));
    switch (state) {
        case ScreenState::MainMenu:
            return std::make_unique<Screens::MenuScreen>(_data);
        case ScreenState::Game:
            return std::make_unique<Screens::GameScreen>(_data, settings);
        case ScreenState::Pause:
            return std::make_unique<Screens::PauseScreen>(_data);
        case ScreenState::Settings:
           return std::make_unique<Screens::SettingsScreen>(_data, settings);
        default:
            throw std::runtime_error("Unknown screen state");
    }
}