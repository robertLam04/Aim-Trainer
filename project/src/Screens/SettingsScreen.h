#pragma once

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "Screen.h"
#include "Button.h"
#include "GameData.h"
#include "Settings.h"
#include "ScreenState.h"

namespace Screens {

    class SettingsScreen : public Screen {
    private:
        GameDataRef _data;
        sf::RenderWindow* window;

        sf::Text title;
        sf::Text header;

        Button menu_button;
        Button easy_button;
        Button medium_button;
        Button hard_button;

        ScreenState next_screen;

        Settings settings;

    public:

        SettingsScreen(GameDataRef data, Settings& settings);

        ~SettingsScreen() override = default;
        
        void init() override;

        void onExit() override;

        void draw() const override;

        void handleEvents(sf::Event event) override;

        void update() override;

        ScreenState getNextScreen() override;
        
        ScreenState getThisScreen() override;

    };

}