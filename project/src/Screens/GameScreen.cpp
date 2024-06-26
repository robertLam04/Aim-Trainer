#include <spdlog/spdlog.h>
#include "GameScreen.h"
#include "GameData.h"
#include "Entities/CircleTarget.h"
#include "Spawners/BasicSpawner.h"
#include "Spawners/EasySpawner.h"
#include "Spawners/MediumSpawner.h"
#include "Logger.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"
#include "PauseScreen.h"


namespace Screens {

    GameScreen::GameScreen(GameDataRef data, const Settings& settings)
    : _data(data)
    , next_screen(std::nullopt)
    , settings(settings)
    , crosshair()
    {   
        console->info("Difficulty: {}", settings.difficulty);
        if (settings.difficulty == 1) {
            spawner = new Spawners::BasicSpawner(_data);
            spawner->init(1);
        } else if (settings.difficulty == 2) {
            spawner = new Spawners::EasySpawner(_data);
            spawner->init(2);
        } else {
            spawner = new Spawners::MediumSpawner(_data);
            spawner->init(3);
        }
    }

    GameScreen::GameScreen(const GameScreen& paused_screen)
    : _data(paused_screen._data)
    , spawner(paused_screen.spawner)
    , next_screen(std::nullopt)
    , settings(paused_screen.settings)
    , crosshair(paused_screen.crosshair)
    {}


    void GameScreen::init() {

        clock.restart();
        
        sf::Image cursorImage = crosshair.getTexture().copyToImage();
        sf::Vector2u imageSize = cursorImage.getSize();
        sf::Cursor cursor;
        if (cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(imageSize.x / 2, imageSize.y / 2))) {
            _data->window.setMouseCursor(cursor);
        } else {
            console->error("Failed to load cursor");
        }
        
    }

    void GameScreen::draw() const {
        this->_data->window.clear(sf::Color(0,0,0));
        spawner->draw(&this->_data->window);
    }

    void GameScreen::handleEvents(sf::Event event) {

        sf::Vector2f mousePosf = _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window));
        sf::Cursor defaultCursor;

        switch (event.type) {
            case sf::Event::Closed:
                defaultCursor.loadFromSystem(sf::Cursor::Arrow);
                _data->window.setMouseCursor(defaultCursor);
                this->_data->window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

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
                    next_screen = std::make_unique<PauseScreen>(_data, *this);
                    console->info("Game paused");
                }
                break;
            default:
                break;
        }
    }

    void GameScreen::update() {
        float deltaTime = clock.restart().asSeconds();
        auto* targets = spawner->getTargets();
        for (auto& target : *targets) {
            target->update(deltaTime);
        }
        spawner->update();
    }

    const Settings& GameScreen::getSettings() {
        return settings;
    }
        
    std::optional<std::unique_ptr<Screen>> GameScreen::getNextScreen() {
        return std::move(next_screen);
    }

}