#pragma once

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

#include "Screen.h"
#include "Button.h"
#include "GameData.h"
#include "Settings.h"
#include "ScreenState.h"

namespace Screens {

    class MenuScreen : public Screen {
    private:
        GameDataRef _data;
        sf::RenderWindow* window;

        sf::Text title;

        Button play_button;
        Button settings_button;
        Button exit_button;

        ScreenState next_screen;

        Settings settings;

    public:

        MenuScreen(GameDataRef data);

        ~MenuScreen() override = default;
        
        void init() override;

        void onExit() override;

        void draw() const override;

        void handleEvents(sf::Event event) override;

        void update() override;

        ScreenState getNextScreen() override;

        ScreenState getThisScreen() override;

    };

}