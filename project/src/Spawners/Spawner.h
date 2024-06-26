#ifndef SPAWNER_H
#define SPAWNER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Entities/Entity.h"
#include "GameData.h"
#include <vector>
#include <memory>

namespace Spawners {

class Spawner {

public:
    virtual ~Spawner() = default;
    virtual void init(int nStartingEntities) = 0;
    virtual void deleteEntity(int entityId) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow* window) const = 0;
    virtual bool isOverlapping(const Entities::Entity& targetA, const Entities::Entity& targetB) const = 0;
    virtual std::vector<std::unique_ptr<Entities::Entity>>* getTargets() = 0;
    
};

}

#endif //SPAWNER_H