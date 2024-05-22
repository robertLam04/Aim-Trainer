#include <spdlog/spdlog.h>
#include "GameScreen.h"
#include "GameData.h"
#include "Entities/CircleTarget.h"
#include "Spawners/Spawner.h"
#include "Logger.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"
#include "PauseScreen.h"


namespace Screens {

    GameScreen::GameScreen(GameDataRef data, const Settings& settings)
    : window(&_data->window)
    , _data(data)
    , next_screen(std::nullopt)
    , settings(settings)
    {
        spawner = new Spawners::Spawner(_data);
    }

    GameScreen::GameScreen(const GameScreen& paused_screen)
        : window(paused_screen.window)
        , _data(paused_screen._data)
        , spawner(paused_screen.spawner)
        , next_screen(std::nullopt)
        , settings(paused_screen.settings)
    {}

    void GameScreen::init() {
        console->info("Difficulty: {}", settings.difficulty);
        if (settings.difficulty == 1) {
            spawner->init(1);
        } else if (settings.difficulty == 2 ){
            spawner->init(2);
        } else {
            spawner->init(3);
        }
        
    }

    void GameScreen::draw() const {
        window->clear(sf::Color(120,56,94));
        spawner->draw(window);
    }

    void GameScreen::handleEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    sf::Vector2f mousePosf = _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window));

                    //TODO: use Quadtrees instead of a vector to store entities
                    auto* targets = spawner->getTargets();
                    auto it = targets->begin();
                    while (it != targets->end()) {
                        if ((*it)->contains(mousePosf)) {
                            std::cout << "inside" << std::endl;
                            it = targets->erase(it);  // Remove element and advance iterator
                        } else {
                            ++it;  // Only advance iterator if no erase happened
                        }
                    }
                }
                break;
            case sf::Event::KeyPressed: 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    next_screen = std::move(std::make_unique<PauseScreen>(_data, *this));
                    console->info("Game paused");
                }
                break;
            default:
                break;
        }
    }

    void GameScreen::update() {
        spawner->update();
    }

    const Settings& GameScreen::getSettings() {
        return settings;
    }
        
    std::optional<std::unique_ptr<Screen>> GameScreen::getNextScreen() {
        return std::move(next_screen);
    }

}