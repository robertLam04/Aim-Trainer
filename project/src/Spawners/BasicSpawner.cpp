#include "Logger.h"
#include "BasicSpawner.h"
#include "Entities/CircleTarget.h"
#include "Entities/Entity.h"
#include "GameData.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include <memory>
#include <random>
#include <cmath>

namespace Spawners {

    BasicSpawner::BasicSpawner(GameDataRef _data)
        : running(true), texture(_data->target_texture) {}

    BasicSpawner::~BasicSpawner() {}

    void BasicSpawner::init(int nStartingEntities) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> sizeDist(10.0f, 50.0f);
        std::uniform_real_distribution<float> positionDistX(50.0f, 750.0f);
        std::uniform_real_distribution<float> positionDistY(50.0f, 550.0f);

        while (targets.size() < nStartingEntities) {
            console->debug("while overlaps");

            Velocity velocity;
            float radius = sizeDist(gen);
            sf::CircleShape circle(radius);
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            circle.setTexture(&texture);

            sf::Vector2f position(positionDistX(gen), positionDistY(gen));
            auto candidate = std::make_unique<Entities::CircleTarget>(circle, position, velocity, 100000000.0f, targetId);
            console->debug("candidate's position: ({}, {}), candidate's radius: {}", candidate->getPosition().x, candidate->getPosition().y, candidate->getRadius());

            bool overlapping = false;
            for (auto& target : targets) {
                console->debug("candidate radius: {}, candidate x pos {}, target radius: {}, target x pos: {}", candidate->getRadius(), candidate->getPosition().x, target->getBounds().width, target->getPosition().x);
                if (isOverlapping(*candidate, *target)) {
                    overlapping = true;
                    break;
                }
            }

            if (!overlapping) {
                console->debug("Adding target to targets");
                targets.push_back(std::move(candidate));
            }
            console->debug("Targets size: {}", targets.size());
        }
        start();
    }

    void BasicSpawner::deleteEntity(int entityId) {
            auto it = std::remove_if(targets.begin(), targets.end(),
                [entityId](const std::unique_ptr<Entities::Entity>& entity) {
                    return entity->getId() == entityId;
                });

            // If the entity was found, erase it from the vector
            if (it != targets.end()) {
                targets.erase(it, targets.end());
            }
        }

    void BasicSpawner::start() {
        running = true;
        clock.restart();
    }

    void BasicSpawner::stop() {
        running = false;
    }

    void BasicSpawner::update() {
        if (!running) return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> sizeDist(10.0f, 50.0f);
        std::uniform_real_distribution<float> positionDistX(50.0f, 750.0f);
        std::uniform_real_distribution<float> positionDistY(50.0f, 550.0f);

        if (clock.getElapsedTime().asMilliseconds() >= spawnInterval) {
            clock.restart();
            bool spawned = false;
            while (!spawned) {
                Velocity velocity;
                float radius = sizeDist(gen);
                sf::CircleShape circle(radius);
                circle.setOrigin(circle.getRadius(), circle.getRadius());
                circle.setTexture(&texture);

                sf::Vector2f position(positionDistX(gen), positionDistY(gen));
                auto candidate = std::make_unique<Entities::CircleTarget>(circle, position, velocity, 100000000.0f, targetId);

                bool overlapping = false;
                for (auto& target : targets) {
                    if (isOverlapping(*candidate, *target)) {
                        overlapping = true;
                        break;
                    }
                }

                if (!overlapping) {
                    targets.push_back(std::move(candidate));
                    spawned = true;
                }
            }
        }
    }

    void BasicSpawner::draw(sf::RenderWindow* window) const {
        for (const auto& target : targets) {
            target->draw(*window);
        }
    }

    bool BasicSpawner::isOverlapping(const Entities::Entity& candidate, const Entities::Entity& target) const {
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

    std::vector<std::unique_ptr<Entities::Entity>>* BasicSpawner::getTargets() {
        return &targets;
    }


}