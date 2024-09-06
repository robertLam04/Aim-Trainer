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

using namespace std;

namespace Screens {

    GameScreen::GameScreen(GameDataRef data, const Settings& settings)
    : _data(data)
    , next_screen(ScreenState::Game)
    , settings(settings)
    , crosshair()
    {   
        console->info("Difficulty: {}", settings.difficulty);
        if (settings.difficulty == 1) {
            spawner = std::make_unique<Spawners::Spawner>(_data, make_pair<float, float>(50.0f, 50.0f), make_pair<float,float>(-15.0f, 15.0f), make_pair<float,float>(-15.0f, 15.0f), 500.0f, 500.0f); 
            spawner->init(1);
        } else if (settings.difficulty == 2) {
            spawner = std::make_unique<Spawners::Spawner>(_data, make_pair<float, float>(40.0f, 40.0f), make_pair<float,float>(-20.0f, 20.0f), make_pair<float,float>(-20.0f, 20.0f), 300.0f, 10000.0f);  
            spawner->init(2);
        } else {
            spawner = std::make_unique<Spawners::Spawner>(_data, make_pair<float, float>(30.0f, 30.0f), make_pair<float,float>(-25.0f, 25.0f), make_pair<float,float>(-25.0f, 25.0f), 200.0f, 10000.0f); 
            spawner->init(10);
        }
    }

    void GameScreen::init() {

        clock.restart();
        
        sf::Image cursorImage = crosshair.getTexture().copyToImage();
        sf::Vector2u imageSize = cursorImage.getSize();
        if (cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(imageSize.x / 2, imageSize.y / 2))) {
            _data->window.setMouseCursor(cursor);
        } else {
            console->error("Failed to load cursor");
        }

        spawner->start();
        
    }

    void GameScreen::onExit() {
        next_screen = ScreenState::Game;
        spawner->stop();
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
                    spawner->handleClick(mousePosf);
                }
                break;
            case sf::Event::KeyPressed: 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    next_screen = ScreenState::Pause;
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

    ScreenState GameScreen::getNextScreen() {
        return next_screen;
    }

    ScreenState GameScreen::getThisScreen() {
        return ScreenState::Game;
    }

}