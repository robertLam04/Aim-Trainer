#include "SettingsScreen.h"
#include "MenuScreen.h"
#include "Logger.h"
#include "Settings.h"

namespace Screens {

    SettingsScreen::SettingsScreen(GameDataRef data, Settings& settings) 
    : _data(data)
    , window(&_data->window)
    , next_screen(ScreenState::Settings)
    , settings(settings)
    {}

    void SettingsScreen::init() {

        title.setString("Settings");
        title.setFillColor(sf::Color(200, 200, 200));
        title.setOutlineThickness(0.5f);
        title.setFont(_data->title_font);
        title.setCharacterSize(45);
        title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height /2);
        title.setPosition(
            _data->window.getSize().x / 2,
            _data->window.getSize().y / 2 - 175.0f
        );

        menu_button = Button(sf::Vector2f(_data->window.getSize().x / 2,
            _data->window.getSize().y / 2 - 100.0f), _data->menu_button);
        menu_button.setScale(0.2f, 0.2f);

        header.setString("Select a difficulty");
        header.setFillColor(sf::Color(200, 200, 200));
        header.setOutlineThickness(0.5f);
        header.setFont(_data->title_font);
        header.setCharacterSize(24);
        header.setOrigin(header.getLocalBounds().width / 2, header.getLocalBounds().height /2);
        header.setPosition(
            _data->window.getSize().x / 2,
            _data->window.getSize().y / 2 - 25.0f
        );

        easy_button = Button(sf::Vector2f(_data->window.getSize().x / 2 - 100.0f,
            _data->window.getSize().y / 2 + 25.0f), _data->easy_button);
        easy_button.setScale(0.2f, 0.2f);

        medium_button = Button(sf::Vector2f(_data->window.getSize().x / 2,
            _data->window.getSize().y / 2 + 25.0f), _data->medium_button);
        medium_button.setScale(0.2f, 0.2f);

        hard_button = Button(sf::Vector2f(_data->window.getSize().x / 2 + 100.0f,
            _data->window.getSize().y / 2 + 25.0f), _data->hard_button);
        hard_button.setScale(0.2f, 0.2f);

    }

    void SettingsScreen::onExit() {}

    void SettingsScreen::draw() const {
        window->clear(sf::Color(0, 0, 0));
        window->draw(title);
        window->draw(header);
        menu_button.draw(window);
        easy_button.draw(window);
        medium_button.draw(window);
        hard_button.draw(window);
    }

    void SettingsScreen::handleEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2f mousePosf = _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window));

                    if (menu_button.clickable() && menu_button.contains(mousePosf)) {
                        menu_button.click();
                        settings.saveSettings("/home/rjlam55/Aim-Trainer/project/Settings.txt");
                        next_screen = ScreenState::MainMenu;
                    }

                    if (easy_button.clickable() && easy_button.contains(mousePosf)) {
                        easy_button.click();
                        settings.difficulty = 1;
                    }

                    if (medium_button.clickable() && medium_button.contains(mousePosf)) {
                        medium_button.click();
                        settings.difficulty = 2;
                    }

                    if (hard_button.clickable() && hard_button.contains(mousePosf)) {
                        hard_button.click();
                        settings.difficulty = 3;
                    }
                    
                }
                break;
            default:
                break;
            }
    }

    void SettingsScreen::update() {
        menu_button.update();

        switch (settings.difficulty) {
            case 1:
                easy_button.setColor(sf::Color(145, 4, 4));
                medium_button.setColor(sf::Color::White);
                hard_button.setColor(sf::Color::White);
                break;
            case 2:
                medium_button.setColor(sf::Color(145, 4, 4));
                easy_button.setColor(sf::Color::White);
                hard_button.setColor(sf::Color::White);
                break;
            case 3:
                hard_button.setColor(sf::Color(145, 4, 4));
                easy_button.setColor(sf::Color::White);
                medium_button.setColor(sf::Color::White);
                break;
            default:
                break;
        }
        
        easy_button.update();
        hard_button.update();
        medium_button.update();
    }
    

    ScreenState SettingsScreen::getNextScreen() {
        return next_screen;
    }

    ScreenState SettingsScreen::getThisScreen() {
        return ScreenState::Settings;
    }

}