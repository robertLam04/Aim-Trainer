#pragma once

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "Spawners/Spawner.h"
#include "Screen.h"
#include "Button.h"
#include "GameData.h"
#include "Settings.h"

namespace Screens {

class GameScreen : public Screen {
private:
    GameDataRef _data;
    sf::RenderWindow* window;
    Spawners::Spawner* spawner;
    std::optional<std::unique_ptr<Screen>> next_screen;

    Settings settings;

public:

    GameScreen(GameDataRef data, const Settings& settings);
    GameScreen(const GameScreen& paused_screen);

    ~GameScreen() override = default;
    
    void init() override;

    void draw() const override;

    void handleEvents(sf::Event event) override;

    void update() override;

    const Settings& getSettings();

    std::optional<std::unique_ptr<Screen>> getNextScreen() override;

};

}