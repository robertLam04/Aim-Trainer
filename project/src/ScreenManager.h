#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <memory>
#include <stack>
#include <unordered_map>
#include <functional>
#include "Settings.h"
#include "ScreenState.h"
#include "Screens/Screen.h"
#include "GameData.h"
#include "Logger.h"

class ScreenManager {
public:
    ScreenManager(ScreenState initialState, GameDataRef _data, Settings settings);

    void handleEvents(sf::Event event);
    void update();
    void draw() const;
    void pushState(ScreenState newState);
    void popState();

private:
    std::unique_ptr<Screens::Screen> createState(ScreenState state);

    std::stack<std::unique_ptr<Screens::Screen>> stateStack;
    ScreenState currentState;

    Settings settings;
    GameDataRef _data;
};

#endif // SCREENMANAGER_H