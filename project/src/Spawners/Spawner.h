#ifndef MED_SPAWNER_H
#define MED_SPAWNER_H

#include "SpatialHash.h"
#include "GameData.h"
#include <spdlog/spdlog.h>
#include <random>
#include "Logger.h"
#include <cmath>
#include <set>

using namespace std;

namespace Spawners {

class Spawner {
private:
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<float> sizeDist;
    uniform_real_distribution<float> veloDistX;
    uniform_real_distribution<float> veloDistY;
    uniform_real_distribution<float> positionDistX;
    uniform_real_distribution<float> positionDistY;

    sf::Texture& texture;
    sf::Clock clock;
    float spawnInterval;
    float lifeTime;
    vector<unique_ptr<Entities::Entity>> targets;
    unique_ptr<SpatialHash> map;
    set<int> idsToDelete;

    int targetId = 0;
    
    bool running = false;

    GameDataRef _data;

    void spawnTarget();
    
public:
    Spawner(GameDataRef _data, pair<float, float> sizeDist, pair<float, float> veloDistX, pair<float, float> veloDistY, float spawnInterval, float lifeTime);

    void init(int nStartingEntities);
    void deleteEntity(int entityId);
    void start();
    void stop();
    void update();
    void handleClick(sf::Vector2f mousePos);
    void draw(sf::RenderWindow* window) const;
    bool isOverlapping(const Entities::Entity& targetA, const Entities::Entity& targetB) const;
    vector<unique_ptr<Entities::Entity>>* getTargets();
         
};

}

#endif //MED_SPAWNER_H