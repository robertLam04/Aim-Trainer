#include "Crosshair.h"
#include "SFML/Graphics.hpp"

void Crosshair::createTexture() {
    // Define image size
    const unsigned int imageSize = 100;

    // Create an image with transparent background
    sf::RenderTexture renderTexture;
    renderTexture.create(imageSize, imageSize);
    renderTexture.clear(sf::Color::Transparent);

    // Create vertical line
    sf::RectangleShape verticalLine(sf::Vector2f(config.width, config.length));
    verticalLine.setFillColor(config.color);
    verticalLine.setOrigin(config.width / 2, config.length / 2);
    verticalLine.setPosition(imageSize / 2, imageSize / 2 - config.offset);
    renderTexture.draw(verticalLine);
    verticalLine.setPosition(imageSize / 2, imageSize / 2 + config.offset);
    renderTexture.draw(verticalLine);

    // Create horizontal line
    sf::RectangleShape horizontalLine(sf::Vector2f(config.length, config.width));
    horizontalLine.setFillColor(config.color);
    horizontalLine.setOrigin(config.length / 2, config.width / 2);
    horizontalLine.setPosition(imageSize / 2 - config.offset, imageSize / 2);
    renderTexture.draw(horizontalLine);
    horizontalLine.setPosition(imageSize / 2 + config.offset, imageSize / 2);
    renderTexture.draw(horizontalLine);

    // Display the render texture to update it with the drawn lines
    renderTexture.display();

    texture = renderTexture.getTexture();
    
}


Crosshair::Crosshair() 
{
    createTexture();
}

sf::Texture Crosshair::getTexture() {
    return texture;
}