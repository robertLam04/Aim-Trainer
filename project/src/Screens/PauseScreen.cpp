#include <optional>

#include "MenuScreen.h"
#include "PauseScreen.h"
#include "GameScreen.h"
#include "Logger.h"

namespace Screens {

    PauseScreen::PauseScreen(GameDataRef data, GameScreen paused_screen) 
    : _data(data)
    , window(&_data->window)
    , next_screen(std::nullopt)
    , paused_screen(paused_screen)
    {}

    void PauseScreen::init() {

        title.setString("Paused");
        title.setFillColor(sf::Color(135, 206, 235));
        title.setOutlineThickness(0.5f);
        title.setFont(_data->title_font);
        title.setCharacterSize(60);
        title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height /2);
        title.setPosition(
            _data->window.getSize().x / 2,
            _data->window.getSize().y / 2 - 110.0f
        );

        resume_button = Button(sf::Vector2f(_data->window.getSize().x / 2,
            _data->window.getSize().y / 2 - 25.0f), _data->resume_button);
        resume_button.setScale(0.2f, 0.2f);

        restart_button = Button(sf::Vector2f(_data->window.getSize().x / 2,
            _data->window.getSize().y / 2 + 25.0f), _data->restart_button);
        restart_button.setScale(0.2f, 0.2f);

        exit_button = Button(sf::Vector2f(_data->window.getSize().x / 2,
            _data->window.getSize().y / 2 + 75.0f), _data->exit_button);
        exit_button.setScale(0.2f, 0.2f);

    }

    void PauseScreen::draw() const {
        window->clear(sf::Color(0,0,0));
        window->draw(title);
        resume_button.draw(window);
        restart_button.draw(window);
        exit_button.draw(window);
    }

    void PauseScreen::handleEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    sf::Vector2f mousePosf = _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window));

                    if (resume_button.clickable() && resume_button.contains(mousePosf)) {
                        resume_button.click();
                        console->info("Resuming game");
                        console->debug("Creating new GameScreen from paused_screen");
                        next_screen = std::make_unique<GameScreen>(paused_screen);
                        console->debug("New GameScreen created successfully");    
                    }

                    if (restart_button.clickable() && restart_button.contains(mousePosf)) {
                        restart_button.click();
                        console->info("Restarting");
                        next_screen = std::make_unique<GameScreen>(_data, paused_screen.getSettings());
                    }

                    if (exit_button.clickable() && exit_button.contains(mousePosf)) {
                        exit_button.click();
                        console->info("Exiting to menu");
                        next_screen = std::make_unique<MenuScreen>(_data);
                    }
                }
                break;
            default:
                break;
        }
    }

    void PauseScreen::update() {
        resume_button.update();
        restart_button.update();
        exit_button.update();
    }

    std::optional<std::unique_ptr<Screen>> PauseScreen::getNextScreen() {
        return std::move(next_screen);
    }

}