#ifndef CIRCLE_TARGET_H
#define CIRCLE_TARGET_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "HitBox.h"

namespace Entities {

class CircleTarget : public Entity {
private:
    sf::CircleShape _circle;
    Velocity velo;
    HitBox _hitbox;
    sf::Clock clock;
    float age = 0.0f;
    float lifetime;
    int id;

public: 
    CircleTarget(sf::CircleShape circle, sf::Vector2f pos, Velocity velocity, float lifetime, int id);

    ~CircleTarget() override = default;
    
    void draw(sf::RenderWindow& w) const override;
    void setPosition(sf::Vector2f pos) override;
    void setPosition(float x, float y) override;
    void setVelocity(float x, float y) override;
    void setTexture(const sf::Texture& texture) override;
    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;
    Velocity getVelocity() const override;
    bool contains(const sf::Vector2f& point) const override;
    void update(float time) override;
    bool isExpired() const override;
    std::vector<sf::Vector2f> getKeyPoints() const override;
    int getId() const override;
    float getRadius() const;
};

}

#endif