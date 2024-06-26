#include "Logger.h"
#include "MediumSpawner.h"
#include "Entities/CircleTarget.h"
#include "GameData.h"
#include "Velocity.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include <memory>

namespace Spawners {

    MediumSpawner::MediumSpawner(GameDataRef _data)
    : gen(rd())
    , sizeDist(4.0f, 4.0f)
    , veloDistX(-1.0f, 1.0f)
    , veloDistY(-1.0f, 1.0f)
    , positionDistX(50.0f, 750.0f)
    , positionDistY(50.0f, 550.0f)
    , _data(_data)
    , texture(_data->target_texture)
    , map(160, 120, 800.0f, 600.0f)
    {}

    void MediumSpawner::init(int nStartingEntities) {

        bool overlaps = false;
        while (targets.size() < nStartingEntities) {
            console->debug("while overlaps");

            Velocity velo(veloDistX(gen), veloDistY(gen));
            velo.normalizeTo(15.0f);
            float radius = sizeDist(gen);
            sf::CircleShape circle(radius);
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            texture.setSmooth(true);
            circle.setFillColor(sf::Color::Red);

            // Get random position
            sf::Vector2f position(positionDistX(gen), positionDistY(gen));
            
            auto candidate = std::make_unique<Entities::CircleTarget>(circle, position, velo, 100000.0f, targetId);
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
                targets.push_back(std::move(candidate));
                targetId++;
            }
            console->debug("Targets size: {}", targets.size());
        } 
        
        start();
    }

    void MediumSpawner::deleteEntity(int entityId) {
       // Remove the entity from the vector
        console->debug("Attempting to erase entity with ID: {}", entityId);
        auto it = std::remove_if(targets.begin(), targets.end(),
            [entityId](const std::unique_ptr<Entities::Entity>& entity) {
                return entity->getId() == entityId;
            });

        // If the entity was found, erase it from the vector
        if (it != targets.end()) {
            targets.erase(it, targets.end());
            console->debug("Entity erased");
        }
    }

    void MediumSpawner::start() {
        running = true;
        clock.restart();
    }

    void MediumSpawner::stop() {
        running = false;
    }

    void MediumSpawner::update() {    
        if (!running) return;

        //Change directions if hitting a wall
        auto isOutsideWindow = [](const sf::FloatRect& bounds, const sf::RenderWindow& window) {
            sf::Vector2u windowSize = window.getSize();
            sf::FloatRect windowRect(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

            return !windowRect.contains(bounds.left, bounds.top) ||
                !windowRect.contains(bounds.left + bounds.width, bounds.top) ||
                !windowRect.contains(bounds.left, bounds.top + bounds.height) ||
                !windowRect.contains(bounds.left + bounds.width, bounds.top + bounds.height);
        };


        auto collisions = map.detectCollisions();
        console->debug("done detecting collisions");
        std::set<int> idsToDelete;
        
        for (const auto& collision : collisions) {
            auto cell = collision.first;
            auto collidingTargets = collision.second;

            for (auto it = collidingTargets.begin(); it != collidingTargets.end(); ++it) {
                idsToDelete.insert((*it)->getId());
            }
            
        }

        for (auto it = targets.begin(); it != targets.end();) {
            if ((*it)->isExpired()) {
                console->debug("Erasing expired entity");
                idsToDelete.insert((*it)->getId());
                ++it;
                // Since deleteEntity removes the element from the vector, 
                // do not increment the iterator; erase returns the next valid iterator
            } else {
                /**/
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

        // Delete collected ids
        for (int id : idsToDelete) {
            deleteEntity(id);
        }

        /* MATH TIME: */


        if (clock.getElapsedTime().asMilliseconds() >= spawnInterval) {
            clock.restart();
            bool spawned = false;
            while (!spawned) {
                // Get circle with random radius, angle, speed
                Velocity velo(veloDistX(gen), veloDistY(gen));
                velo.normalizeTo(15.0f);
                float radius = sizeDist(gen);
                sf::CircleShape circle(radius); // Create the circle as a regular object
                circle.setOrigin(circle.getRadius(), circle.getRadius());
                texture.setSmooth(true);
                circle.setFillColor(sf::Color::Red);

                // Get random position
                sf::Vector2f position(positionDistX(gen), positionDistY(gen));
                
                auto candidate = std::make_unique<Entities::CircleTarget>(circle, position, velo, 100000.0f, targetId);

                bool overlapping = false;
                for (auto& target : targets) {
                    if (isOverlapping(*candidate, *target)) {
                        overlapping = true;
                        break;
                    }
                }

                if (!overlapping) {
                    targets.push_back(std::move(candidate)); // Pass the circle by value
                    targetId++; //Increment target ID
                    spawned = true;
                }
            }
        }
        map.clear();
        for (auto it = targets.begin(); it != targets.end(); ++it) {
            map.insert(it->get());
        }
    }

    void MediumSpawner::draw(sf::RenderWindow* window) const {
        for (const auto& target : targets) {
            if (!target) {
                continue;
            }
            console->debug("Drawing target {}", target->getId());
            target->draw(*window);

        }
    }

    bool MediumSpawner::isOverlapping(const Entities::Entity& candidate, const Entities::Entity& target) const {
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
    
    std::vector<std::unique_ptr<Entities::Entity>>* MediumSpawner::getTargets() {
        return &targets;
    }


}