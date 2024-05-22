#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class GameData {
public:
    GameData();

    sf::RenderWindow window;

    sf::Texture menu_button;
    sf::Texture save_button;
    sf::Texture easy_button;
    sf::Texture medium_button;
    sf::Texture hard_button;
    sf::Texture target_texture;
    sf::Texture pause_button;
    sf::Texture play_button;
    sf::Texture exit_button;
    sf::Texture settings_button;
    sf::Texture resume_button;
    sf::Texture restart_button;
    sf::Texture close_button;


    sf::Font title_font;
    
};

using GameDataRef = std::shared_ptr<GameData>;

#endif