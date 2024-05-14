#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>

namespace Screens {

class Screen {
private:
    sf::RenderWindow* window;
    
public:
    virtual ~Screen();

    virtual void init() = 0;

    virtual void draw() const = 0;

    virtual void handleEvents(sf::Event event) = 0;

    virtual void update() = 0;

};

inline Screen::~Screen() {}

}

#endif