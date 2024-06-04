#ifndef EASY_SPAWNER_H
#define EASY_SPAWNER_H

#include "Spawner.h"
#include <spdlog/spdlog.h>

namespace Spawners {

class EasySpawner : public Spawner {
private:
    sf::Texture& texture;
    sf::Clock clock;
    float spawnInterval = 2000.0f;
    std::vector<std::unique_ptr<Entities::Entity>> targets;
    
    GameDataRef _data;
    bool running = false;
    
public:
    EasySpawner(GameDataRef _data);
    ~EasySpawner();

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

#endif //EASY_SPAWNER_H