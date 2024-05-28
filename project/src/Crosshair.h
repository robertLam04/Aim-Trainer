#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <SFML/Graphics.hpp>

struct CrosshairConfig {
    float offset;
    float width;
    float length;
    sf::Color color;

    //Default constructor
    CrosshairConfig()
    : offset(6.0f)
    , width(4.0f)
    , length(6.0f)
    , color(sf::Color::Green)
    {}

};

class Crosshair {
private:
    CrosshairConfig config;
    sf::Texture texture;

    void createTexture();

public:

    Crosshair();

    sf::Texture getTexture();

};


#endif 