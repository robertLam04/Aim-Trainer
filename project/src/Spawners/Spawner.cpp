#include "Logger.h"
#include "Spawner.h"
#include "Entities/CircleTarget.h"
#include "GameData.h"
#include "Velocity.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include <memory>

using namespace std;

namespace Spawners {

    Spawner::Spawner(GameDataRef _data, pair<float, float> sizeDist, pair<float, float> veloDistX, pair<float,float> veloDistY, float spawnInterval, float lifeTime)
    : gen(rd())
    , sizeDist(sizeDist.first, sizeDist.second)
    , veloDistX(veloDistX.first, veloDistX.second)
    , veloDistY(veloDistY.first, veloDistY.second)
    , positionDistX(50.0f, 750.0f)
    , positionDistY(50.0f, 550.0f)
    , spawnInterval(spawnInterval)
    , lifeTime(lifeTime)
    , _data(_data)
    , texture(_data->target_texture)
    {
        
        float diameter = 2 *  sizeDist.second;
        int widthCells = 800.0 / diameter;
        int heightCells = 600.0 / diameter;
        map = std::make_unique<SpatialHash>(widthCells, heightCells, 800.0f, 600.0f);
    }

    void Spawner::init(int nStartingEntities) {

        while (targets.size() < nStartingEntities) {
            spawnTarget();
        } 
        start();
    }

    void Spawner::deleteEntity(int entityId) {
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

    void Spawner::start() {
        running = true;
        clock.restart();
    }

    void Spawner::stop() {
        running = false;
    }

    void Spawner::update() {
        if (!running) return;

        //Entity -> Entity collision handling
        auto collisions = map->detectCollisions();
        for (const auto& collision : collisions) {
            auto cell = collision.first;
            auto collidingTargets = collision.second;

            for (size_t i = 0; i < collidingTargets.size(); i++) {
                for (size_t j = i + 1; j < collidingTargets.size(); j++) {
                    auto pos_i = collidingTargets.at(i)->getPosition();
                    auto pos_j = collidingTargets.at(j)->getPosition();
                    auto range = (collidingTargets.at(i)->getBounds().height / 2) + (collidingTargets.at(j)->getBounds().height / 2);
                    float distance = std::sqrt(std::pow(pos_i.x - pos_j.x, 2) + std::pow(pos_i.y - pos_j.y, 2));
                    
                    if (range >= distance) {
                        // Get current velocities
                        auto vel_i = collidingTargets.at(i)->getVelocity();
                        auto vel_j = collidingTargets.at(j)->getVelocity();

                        // Calculate the normal vector
                        sf::Vector2f normal = pos_j - pos_i;
                        normal /= distance;  // Normalize the normal vector

                        Velocity relativeVelocity = vel_j - vel_i;
                        float velocityAlongNormal = relativeVelocity.getX() * normal.x + relativeVelocity.getY() * normal.y;

                        // If objects are moving away from each other, do nothing
                        if (velocityAlongNormal > 0) {
                            continue;
                        }

                        sf::Vector2f impulse = -velocityAlongNormal * normal;

                        auto vel_i_x = vel_i.getX() - impulse.x;
                        auto vel_i_y = vel_i.getY() - impulse.y;
                        auto vel_j_x = vel_j.getX() + impulse.x;
                        auto vel_j_y = vel_j.getY() + impulse.y;

                        // Update velocities
                        collidingTargets.at(i)->setVelocity(vel_i_x, vel_i_y);
                        collidingTargets.at(j)->setVelocity(vel_j_x, vel_j_y);
                    }
                }
                
            }
            
        }

        //Add expired entities to delete pool
        for (auto it = targets.begin(); it != targets.end();) {
            if ((*it)->isExpired()) {
                idsToDelete.insert((*it)->getId());
                ++it;
            } else {
                ++it; 
            }
        }

        //Check for boundary collisions (first is left/right, second is top/bottom)
        auto entitiesOutside = map->isOutsideWindow();
        for (auto it = entitiesOutside.first.begin(); it != entitiesOutside.first.end(); ++it) {
            auto currentVelo = (*it)->getVelocity();
            (*it)->setVelocity(-currentVelo.getX(), currentVelo.getY());
        }

        for (auto it = entitiesOutside.second.begin(); it != entitiesOutside.second.end(); ++it) {
            auto currentVelo = (*it)->getVelocity();
            (*it)->setVelocity(currentVelo.getX(), -currentVelo.getY());
        }

        // Delete collected ids
        for (int id : idsToDelete) {
            deleteEntity(id);
        }
        idsToDelete.clear();
        
        //Spawn a new target
        if (clock.getElapsedTime().asMilliseconds() >= spawnInterval) {
            clock.restart();
            spawnTarget();
        }

        //Clear and refill the map with the new targets
        map->clear();
        for (auto it = targets.begin(); it != targets.end(); ++it) {
            map->insert(it->get());
        }

    }

    void Spawner::handleClick(sf::Vector2f mousePos) { 
        auto it = targets.begin();
        while (it != targets.end()) {
            if ((*it)->contains(mousePos)) {
                std::cout << "inside" << std::endl;
                idsToDelete.insert((*it)->getId());
                ++it;
            } else {
                ++it;  // Only advance iterator if no erase happened
            }
        }
    }

    void Spawner::draw(sf::RenderWindow* window) const {
        for (const auto& target : targets) {
            if (!target) {
                continue;
            }
            console->debug("Drawing target {}", target->getId());
            target->draw(*window);
        }
    }

    bool Spawner::isOverlapping(const Entities::Entity& candidate, const Entities::Entity& target) const {
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
    
    std::vector<std::unique_ptr<Entities::Entity>>* Spawner::getTargets() {
        return &targets;
    }

    void Spawner::spawnTarget() {
        bool spawned = false;
        while (!spawned) {
            Velocity velo(veloDistX(gen), veloDistY(gen));
            float radius = sizeDist(gen);
            sf::CircleShape circle(radius); // Create the circle as a regular object
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            texture.setSmooth(true);
            circle.setFillColor(sf::Color::Red);

            sf::Vector2f position(positionDistX(gen), positionDistY(gen));
            
            auto candidate = std::make_unique<Entities::CircleTarget>(circle, position, velo, lifeTime, targetId);

            bool overlapping = false;
            for (auto& target : targets) {
                if (isOverlapping(*candidate, *target)) {
                    overlapping = true; 
                    break;
                }
            }

            if (!overlapping) {
                targets.push_back(std::move(candidate));
                targetId++; 
                spawned = true;
            }
        }
    }
}