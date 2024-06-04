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
    : offset(8.0f)
    , width(3.0f)
    , length(6.90f)
    , color(sf::Color(0, 255, 0))
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