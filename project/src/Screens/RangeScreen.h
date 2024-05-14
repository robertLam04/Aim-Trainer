#pragma once

#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Spawners/Spawner.h"
#include "Entities/CircleTarget.h"
#include "Screen.h"

namespace Screens {

class RangeScreen : public Screen {
private:
    sf::RenderWindow* window;
    Spawners::Spawner* spawner;
public:

    RangeScreen(sf::RenderWindow* window, Spawners::Spawner* spawner);

    ~RangeScreen() override = default;
    
    void init() override;

    void draw() const override;

    void handleEvents(sf::Event event) override;

    void update() override;

};


}