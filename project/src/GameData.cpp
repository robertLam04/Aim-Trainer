#include "GameData.h"

GameData::GameData() {

    window.create(sf::VideoMode(800, 600), "Game Window");
    target_texture.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/target_image.png");
    pause_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/pause_button_white.png");
    play_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/play_button.png");
    settings_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/settings_button.png");
    exit_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/exit_button.png");
    resume_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/resume_button.png");
    restart_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/restart_button.png");
    menu_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/menu_button.png");
    save_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/save_button.png");
    easy_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/easy_button.png");
    medium_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/medium_button.png");
    hard_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/hard_button.png");
    close_button.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/close_button.png");
    // Rollbox by Owlkingproject
    title_font.loadFromFile("/home/rjlam55/Aim-Trainer/project/Assets/RollboxRegular-jE2lv.ttf");
    
}