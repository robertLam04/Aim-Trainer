#ifndef BASIC_SPAWNER_H
#define BASIC_SPAWNER_H

#include "Spawner.h"
#include <spdlog/spdlog.h>

namespace Spawners {

class BasicSpawner : public Spawner {
private:
    sf::Texture& texture;
    sf::Clock clock;
    float spawnInterval = 600.0f;
    std::vector<std::unique_ptr<Entities::Entity>> targets;
    
    bool running = false;
    
public:
    BasicSpawner(GameDataRef _data);
    ~BasicSpawner();

    void init(int nStartingEntities) override;
    void deleteEntity(std::vector<std::unique_ptr<Entities::Entity>>::iterator target) override;
    void start() override;
    void stop() override;
    void update() override;
    void draw(sf::RenderWindow* window) const override;
    bool isOverlapping(const Entities::Entity& targetA, const Entities::Entity& targetB) const override;
    std::vector<std::unique_ptr<Entities::Entity>>* getTargets() override;
};

}

#endif //BASIC_SPAWNER_H