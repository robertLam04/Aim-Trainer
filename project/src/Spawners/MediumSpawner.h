#ifndef MED_SPAWNER_H
#define MED_SPAWNER_H

#include "Spawner.h"
#include "SpatialHash.h"
#include <spdlog/spdlog.h>
#include <random>
#include "Logger.h"
#include <cmath>

namespace Spawners {

class MediumSpawner : public Spawner {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> sizeDist;
    std::uniform_real_distribution<float> veloDistX;
    std::uniform_real_distribution<float> veloDistY;
    std::uniform_real_distribution<float> positionDistX;
    std::uniform_real_distribution<float> positionDistY;

    sf::Texture& texture;
    sf::Clock clock;
    float spawnInterval = 10.0f;
    std::vector<std::unique_ptr<Entities::Entity>> targets;
    SpatialHash map;

    int targetId = 0;
    
    bool running = false;

    GameDataRef _data;
    
public:
    MediumSpawner(GameDataRef _data);

    void init(int nStartingEntities) override;
    void deleteEntity(int entityId) override;
    void start() override;
    void stop() override;
    void update() override;
    void draw(sf::RenderWindow* window) const override;
    bool isOverlapping(const Entities::Entity& targetA, const Entities::Entity& targetB) const override;
    std::vector<std::unique_ptr<Entities::Entity>>* getTargets() override;
         
};

}

#endif //MED_SPAWNER_H