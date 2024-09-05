#include "MenuScreen.h"
#include "GameScreen.h"
#include "SettingsScreen.h"
#include "Logger.h"

namespace Screens {

    MenuScreen::MenuScreen(GameDataRef data) 
    : _data(data)
    , window(&_data->window)
    , next_screen(ScreenState::MainMenu)
    {}

    void MenuScreen::init() {

        console->debug("Initializing MenuScreen");

        title.setString("Aim Trainer");
        title.setFillColor(sf::Color(135, 206, 235));
        title.setOutlineThickness(0.5f);
        title.setFont(_data->title_font);
        title.setCharacterSize(60);
        title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
        title.setPosition(
            _data->window.getSize().x / 2,
            _data->window.getSize().y / 2 - 110.0f
        );
        console->debug("Title initialized");

        play_button = Button(sf::Vector2f(_data->window.getSize().x / 2,
            _data->window.getSize().y / 2 - 25.0f), _data->play_button);
        play_button.setScale(0.2f, 0.2f);
        console->debug("Play button initialized");

        settings_button = Button(sf::Vector2f(_data->window.getSize().x / 2,
            _data->window.getSize().y / 2 + 25.0f), _data->settings_button);
        settings_button.setScale(0.2f, 0.2f);
        console->debug("Settings button initialized");

        exit_button = Button(sf::Vector2f(_data->window.getSize().x / 2,
            _data->window.getSize().y / 2 + 75.0f), _data->close_button);
        exit_button.setScale(0.2f, 0.2f);
        console->debug("Exit button initialized");

        console->debug("MenuScreen initialization complete");
    }

    void MenuScreen::onExit() {}

    void MenuScreen::draw() const {
        window->clear(sf::Color(206, 154, 245));
        window->draw(title);
        play_button.draw(window);
        settings_button.draw(window);
        exit_button.draw(window);
    }

    void MenuScreen::handleEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    sf::Vector2f mousePosf = _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window));

                    if (play_button.clickable() && play_button.contains(mousePosf)) {
                        play_button.click();
                        console->info("Playing game");
                        next_screen = ScreenState::Game;
                    }

                    if (settings_button.clickable() && settings_button.contains(mousePosf)) {
                        settings_button.click();
                        console->info("Creating settings screen");
                        next_screen = ScreenState::Settings;
                    }

                    if (exit_button.clickable() && exit_button.contains(mousePosf)) {
                        console->info("Exiting");
                        window->close();
                    }
                }
                break;
            default:
                break;
        }
    }

    void MenuScreen::update() {
        play_button.update();
        settings_button.update();
        exit_button.update();
    }

    ScreenState MenuScreen::getNextScreen() {
        return next_screen;
    }

    ScreenState MenuScreen::getThisScreen() {
        return ScreenState::MainMenu;
    }

}