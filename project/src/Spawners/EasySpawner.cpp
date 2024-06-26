#include "Logger.h"
#include "EasySpawner.h"
#include "Entities/CircleTarget.h"
#include "GameData.h"
#include "Velocity.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include <memory>
#include <random>
#include <cmath>


namespace Spawners {

    EasySpawner::EasySpawner(GameDataRef _data)
    : running(true)
    , _data(_data)
    , texture(_data->target_texture)
    {}

    EasySpawner::~EasySpawner() {}

    void EasySpawner::init(int nStartingEntities) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> sizeDist(25.0f, 50.0f);
        std::uniform_real_distribution<float> veloDistX(-1.0, 1.0f);
        std::uniform_real_distribution<float> veloDistY(-1.0, 1.0f);
        // Assuming screen size of 800x600
        std::uniform_real_distribution<float> positionDistX(50.0f, 750.0f);
        std::uniform_real_distribution<float> positionDistY(50.0f, 550.0f);

        bool overlaps = false;
        while (targets.size() < nStartingEntities) {
            console->debug("while overlaps");

            Velocity velo(veloDistX(gen), veloDistY(gen));
            velo.normalizeTo(10.0f);
            float radius = sizeDist(gen);
            sf::CircleShape circle(radius); // Create the circle as a regular object
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            texture.setSmooth(true);
            circle.setTexture(&texture);

            // Get random position
            sf::Vector2f position(positionDistX(gen), positionDistY(gen));
            
            auto candidate = std::make_unique<Entities::CircleTarget>(circle, position, velo, 3000.0f, targetId);
            console->debug("candidate's position: ({}, {}), candidate's radius: {}", candidate->getPosition().x, candidate->getPosition().y, candidate->getRadius());

            bool overlapping = false;
            for (auto& target : targets) {
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

    void EasySpawner::deleteEntity(int entityId) {
        auto it = std::remove_if(targets.begin(), targets.end(),
            [entityId](const std::unique_ptr<Entities::Entity>& entity) {
                return entity->getId() == entityId;
            });

        // If the entity was found, erase it from the vector
        if (it != targets.end()) {
            targets.erase(it, targets.end());
        }
    }

    void EasySpawner::start() {
        running = true;
        clock.restart();
    }

    void EasySpawner::stop() {
        running = false;
    }

    void EasySpawner::update() {    
        if (!running) return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> sizeDist(25.0f, 50.0f);
        std::uniform_real_distribution<float> veloDistX(-1.0, 1.0f);
        std::uniform_real_distribution<float> veloDistY(-1.0, 1.0f);
        // Assuming screen size of 800x600
        std::uniform_real_distribution<float> positionDistX(50.0f, 750.0f);
        std::uniform_real_distribution<float> positionDistY(50.0f, 550.0f);

        //Change directions if hitting a wall
        auto isOutsideWindow = [](const sf::FloatRect& bounds, const sf::RenderWindow& window) {
            sf::Vector2u windowSize = window.getSize();
            sf::FloatRect windowRect(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

            return !windowRect.contains(bounds.left, bounds.top) ||
                !windowRect.contains(bounds.left + bounds.width, bounds.top) ||
                !windowRect.contains(bounds.left, bounds.top + bounds.height) ||
                !windowRect.contains(bounds.left + bounds.width, bounds.top + bounds.height);
        };

        for (auto it = targets.begin(); it != targets.end(); ) {
            if ((*it)->isExpired()) {
                deleteEntity((*it)->getId());
                // Since deleteEntity removes the element from the vector, 
                // do not increment the iterator; erase returns the next valid iterator
            } else {
                if (isOutsideWindow((*it)->getBounds(), _data->window)) {
                    auto currentVelo = (*it)->getVelocity();
                    sf::FloatRect bounds = (*it)->getBounds();
                    sf::Vector2u windowSize = _data->window.getSize();

                    // Check for left and right walls
                    if (bounds.left < 0 || bounds.left + bounds.width > windowSize.x) {
                        (*it)->setVelocity(-currentVelo.getX(), currentVelo.getY());
                    }

                    // Check for top and bottom walls
                    if (bounds.top < 0 || bounds.top + bounds.height > windowSize.y) {
                        (*it)->setVelocity(currentVelo.getX(), -currentVelo.getY());
                    }
                }
                ++it;  // Only increment the iterator if we did not erase an element
            }
        }

        if (clock.getElapsedTime().asMilliseconds() >= spawnInterval) {
            clock.restart();
            bool spawned = false;
            while (!spawned) {
                // Get circle with random radius, angle, speed
                Velocity velo(veloDistX(gen), veloDistY(gen));
                velo.normalizeTo(10.0f);
                float radius = sizeDist(gen);
                sf::CircleShape circle(radius); // Create the circle as a regular object
                circle.setOrigin(circle.getRadius(), circle.getRadius());
                texture.setSmooth(true);
                circle.setTexture(&texture);

                // Get random position
                sf::Vector2f position(positionDistX(gen), positionDistY(gen));
                
                auto candidate = std::make_unique<Entities::CircleTarget>(circle, position, velo, 3000.0f, targetId);

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

    void EasySpawner::draw(sf::RenderWindow* window) const {
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

    bool EasySpawner::isOverlapping(const Entities::Entity& candidate, const Entities::Entity& target) const {
        std::vector<sf::Vector2f> candidatePoints = candidate.getKeyPoints();
        for (const auto& point : candidatePoints) {
            if (target.contains(point)) {
                return true;
            }
        }

        std::vector<sf::Vector2f> targetPoints = target.getKeyPoints();
        for (const auto& point : targetPoints) {
            if (candidate.contains(point)) {
                return true;
            }
        }

        return false;
    }
    
    std::vector<std::unique_ptr<Entities::Entity>>* EasySpawner::getTargets() {
        return &targets;
    }


}