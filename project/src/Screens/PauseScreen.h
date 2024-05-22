#pragma once

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

#include "GameScreen.h"
#include "Button.h"
#include "GameData.h"

namespace Screens {

class PauseScreen : public Screen {
private:
    GameDataRef _data;
    sf::RenderWindow* window;
    sf::Text title;
    Button resume_button;
    Button exit_button;
    Button restart_button;

    std::optional<std::unique_ptr<Screen>> next_screen;

    GameScreen paused_screen;

public:

    PauseScreen(GameDataRef data, GameScreen paused_screen);

    ~PauseScreen() override = default;
    
    void init() override;

    void draw() const override;

    void handleEvents(sf::Event event) override;

    void update() override;

    std::optional<std::unique_ptr<Screen>> getNextScreen() override;

};

}