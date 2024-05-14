#include "Logger.h"
#include "Spawner.h"
#include "Entities/CircleTarget.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include <memory>
#include <random>
#include <cmath>


namespace Spawners {

    Spawner::Spawner(sf::Texture& texture)
    : running(true)
    , texture(texture)
    {}

    Spawner::~Spawner() {}

    void Spawner::init(int nStartingEntities) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> sizeDist(10.0f, 50.0f);
        // Assuming screen size of 800x600
        std::uniform_real_distribution<float> positionDistX(0.0f, 800.0f);
        std::uniform_real_distribution<float> positionDistY(0.0f, 600.0f);

        bool overlaps = false;
        while (targets.size() < nStartingEntities) {
            console->debug("while overlaps");
            
            // Get circle with random radius
            float radius = sizeDist(gen);
            sf::CircleShape circle(radius); // Create the circle as a regular object
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            circle.setTexture(&texture);

            // Get random position
            sf::Vector2f position(positionDistX(gen), positionDistY(gen));
            
            auto candidate = std::make_unique<Entities::CircleTarget>(circle, texture, position);
            console->debug("candidate's position: ({}, {}), candidate's radius: {}", candidate->getPosition().x, candidate->getPosition().y, candidate->getRadius());

            bool overlapping = false;
            for (auto& target : targets) {
                console->debug("candidate radius: {}, candidate x pos {}, target radius: {}, target x pos: {}", candidate->getRadius(), candidate->getPosition().x, target->getRadius(), target->getPosition().x);
                if (isOverlapping(*candidate, *target)) {
                    overlapping = true;
                    break;
                }
            }

            if (!overlapping) {
                console->debug("Adding target to targets");
                targets.push_back(std::move(candidate)); // Pass the circle by value
            }
            console->debug("Targets size: {}", targets.size());
        } 
        start();
    }

    void Spawner::deleteEntity(std::vector<std::unique_ptr<Entities::CircleTarget>>::iterator target) {
        if (target != targets.end()) {
            targets.erase(target);
        }
    }

    void Spawner::start() {
        running = true;
        clock.restart();
    }

    void Spawner::stop() {
        running = false;
    }

    void Spawner::update() {    
        if (!running) return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> sizeDist(10.0f, 50.0f);
        // Assuming screen size of 800x600
        std::uniform_real_distribution<float> positionDistX(0.0f, 750.0f);
        std::uniform_real_distribution<float> positionDistY(0.0f, 550.0f);

        if (clock.getElapsedTime().asMilliseconds() >= spawnInterval) {
            clock.restart();
            bool spawned = false;
            while (!spawned) {
                // Get circle with random radius
                float radius = sizeDist(gen);
                sf::CircleShape circle(radius); // Create the circle as a regular object
                circle.setOrigin(circle.getRadius(), circle.getRadius());
                circle.setTexture(&texture);

                // Get random position
                sf::Vector2f position(positionDistX(gen), positionDistY(gen));
                
                auto candidate = std::make_unique<Entities::CircleTarget>(circle, texture, position);

                bool overlapping = false;
                for (auto& target : targets) {
                    if (isOverlapping(*candidate, *target)) {
                        overlapping = true;
                        break;
                    }
                }

                if (!overlapping) {
                    targets.push_back(std::move(candidate)); // Pass the circle by value
                    spawned = true;
                }
            }
        }
    }

    void Spawner::draw(sf::RenderWindow* window) const {
        int index = 0;
        for (const auto& target : targets) {
            if (!target) {
                console->error("Target at index {} is null", index);
                continue;
            }
            console->debug("Drawing target {}", index);
            target->draw(*window);
            index++;
        }
    }

    bool Spawner::isOverlapping(const Entities::CircleTarget& candidate, const Entities::CircleTarget& target) const {
        console->debug("running isOverlapping");
        sf::Vector2f diff = candidate.getPosition() - target.getPosition();
        float distanceSquared = diff.x * diff.x + diff.y * diff.y;
        float combinedRadii = candidate.getRadius() + target.getRadius();
        return distanceSquared < combinedRadii * combinedRadii;
    }
    
    std::vector<std::unique_ptr<Entities::CircleTarget>>* Spawner::getTargets() {
        return &targets;
    }

}