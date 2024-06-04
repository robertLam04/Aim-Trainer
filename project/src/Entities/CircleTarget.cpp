#include "CircleTarget.h"
#include "Entity.h"
#include "HitBox.h"
#include "cmath"

namespace Entities {

CircleTarget::CircleTarget(sf::CircleShape circle, sf::Vector2f pos, Velocity velocity)
    : _circle(circle)
    , velo(velocity)
    , _hitbox(*this)
{
    _circle.setPosition(pos);
}

void CircleTarget::draw(sf::RenderWindow& w) const {
    w.draw(_circle);
}

void CircleTarget::setPosition(sf::Vector2f pos) {
    _circle.setPosition(pos);
}

void CircleTarget::setPosition(float x, float y) {
    _circle.setPosition(x, y);
}

void CircleTarget::setVelocity(float x, float y) {
    this->velo.setVelocity(x, y);
}

void CircleTarget::setTexture(const sf::Texture& texture) {
    _circle.setTexture(&texture);
}

sf::Vector2f CircleTarget::getPosition() const {
    return _circle.getPosition();
}

sf::FloatRect CircleTarget::getBounds() const {
    return _circle.getGlobalBounds();
}

Velocity CircleTarget::getVelocity() const {
    return this->velo;
}

bool CircleTarget::contains(const sf::Vector2f& point) const {
    return _hitbox.contains(point);
}

void CircleTarget::update(float time) {
    float speed = velo.getMagnitude();
    
    float distance = speed * time;

    float dx = distance * velo.getX();
    float dy = distance * velo.getY();

    sf::Vector2f position = this->getPosition();

    position.x += dx;
    position.y += dy;

    // Set the new position
    this->setPosition(position);
}

std::vector<sf::Vector2f> CircleTarget::getKeyPoints() const {
    std::vector<sf::Vector2f> points;
    sf::Vector2f center = getPosition();
    float radius = getRadius();
    int numPoints = 36;  // Number of points around the circle

    for (int i = 0; i < numPoints; ++i) {
        float angle = i * (2 * M_PI / numPoints);
        points.push_back(center + sf::Vector2f(radius * std::cos(angle), radius * std::sin(angle)));
    }

    return points;
}

float CircleTarget::getRadius() const {
    return _circle.getRadius();
}

} // namespace Entities