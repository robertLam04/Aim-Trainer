#pragma once

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

#include "GameScreen.h"
#include "Button.h"
#include "GameData.h"
#include "ScreenState.h"

namespace Screens {

class PauseScreen : public Screen {
private:
    GameDataRef _data;
    sf::RenderWindow* window;
    sf::Text title;
    Button resume_button;
    Button exit_button;
    Button restart_button;

    ScreenState next_screen;


public:

    PauseScreen(GameDataRef data);

    ~PauseScreen() override = default;
    
    void init() override;

    void onExit() override;

    void draw() const override;

    void handleEvents(sf::Event event) override;

    void update() override;

    ScreenState getNextScreen() override;

    ScreenState getThisScreen() override;

};

}