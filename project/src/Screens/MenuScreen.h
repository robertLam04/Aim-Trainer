#pragma once

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

#include "Screen.h"
#include "Button.h"
#include "GameData.h"
#include "Settings.h"

namespace Screens {

    class MenuScreen : public Screen {
    private:
        GameDataRef _data;
        sf::RenderWindow* window;

        sf::Text title;

        Button play_button;
        Button settings_button;
        Button exit_button;

        std::optional<std::unique_ptr<Screen>> next_screen;

        Settings settings;

    public:

        MenuScreen(GameDataRef data);

        ~MenuScreen() override = default;
        
        void init() override;

        void draw() const override;

        void handleEvents(sf::Event event) override;

        void update() override;

        std::optional<std::unique_ptr<Screen>> getNextScreen() override;

    };

}