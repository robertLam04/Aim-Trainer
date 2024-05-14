#ifndef SPAWNER_H
#define SPAWNER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Entities/CircleTarget.h"
#include <spdlog/spdlog.h>

namespace Spawners {

class Spawner {
private:
    sf::Texture& texture;
    sf::Clock clock;
    float spawnInterval = 600.0f;
    std::vector<std::unique_ptr<Entities::CircleTarget>> targets;
    
    bool running = false;
    
public:
    Spawner(sf::Texture& texture);
    ~Spawner();
    
    //Initialize starting targets
    void init(int nStartingEntities);

    void deleteEntity(std::vector<std::unique_ptr<Entities::CircleTarget>>::iterator target);
    
    void start();
    void stop();

    void update();
    void draw(sf::RenderWindow* window) const;

    bool isOverlapping(const Entities::CircleTarget& targetA, const Entities::CircleTarget& targetB) const;

    std::vector<std::unique_ptr<Entities::CircleTarget>>* getTargets();

};


}


#endif //SPAWNER_H