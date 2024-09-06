#pragma once

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

#include "Crosshair.h"
#include "Spawners/Spawner.h"
#include "Screen.h"
#include "Button.h"
#include "GameData.h"
#include "Settings.h"
#include "ScreenState.h"

namespace Screens {

class GameScreen : public Screen {
private:
    GameDataRef _data;
    std::unique_ptr<Spawners::Spawner> spawner;
    ScreenState next_screen;

    sf::Clock clock;

    Crosshair crosshair;
    sf::Cursor cursor;

    Settings settings;

public:

    GameScreen(GameDataRef data, const Settings& settings);
    GameScreen(const GameScreen& paused_screen);

    ~GameScreen() override = default;
    
    void init() override;

    void onExit() override;

    void draw() const override;

    void handleEvents(sf::Event event) override;

    void update() override;

    ScreenState getNextScreen() override;

    ScreenState getThisScreen() override;

};

}