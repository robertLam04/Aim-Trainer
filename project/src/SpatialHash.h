#include <unordered_map>
#include <Entities/CircleTarget.h>
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include <set>

/*
    - HashMap<std::pair, target>
    - For every floatrect key in the map, check if the targets are colliding
    - Hash function: (center point + radius) -> specific cell(s)
    - Idea for changeList: https://www.researchgate.net/publication/354065094_Practical_Spatial_Hash_Map_Updates

*/

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        std::size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };
}

class SpatialHash {
private:
    int rows;
    int cols;
    float windowWidth;
    float windowHeight;
    std::unordered_multimap<std::pair<int, int>, Entities::Entity*> map;

    void checkBounds(const sf::FloatRect& bounds, const sf::FloatRect& windowRect,
                     std::set<Entities::Entity*>& top_bottom, std::set<Entities::Entity*>& right_left,
                     Entities::Entity* entity) {
        if (!windowRect.contains(bounds.left, bounds.top) ||
            !windowRect.contains(bounds.left + bounds.width, bounds.top) ||
            !windowRect.contains(bounds.left, bounds.top + bounds.height) ||
            !windowRect.contains(bounds.left + bounds.width, bounds.top + bounds.height)) {
            
            if (bounds.left < 0 || bounds.left + bounds.width > windowWidth) {
                // Left and right walls
                right_left.insert(entity);
            }

            if (bounds.top < 0 || bounds.top + bounds.height > windowHeight) {
                // Top and bottom walls
                top_bottom.insert(entity);
            }
        }
    }

public:
    SpatialHash(int rows, int cols, float windowWidth, float windowHeight)
    : rows(rows)
    , cols(cols)
    , windowWidth(windowWidth)
    , windowHeight(windowHeight)

    {}

    void insert(Entities::Entity* target) {
        auto bounds = target->getBounds();
        float cellWidth = windowWidth / cols;
        float cellHeight = windowHeight / rows;
        std::pair<std::size_t, std::size_t> rangeX = {bounds.left / cellWidth, (bounds.left + bounds.width) / cellWidth};
        std::pair<std::size_t, std::size_t> rangeY = {bounds.top / cellHeight, (bounds.top + bounds.height) / cellHeight};
        for (int i = rangeX.first; i <= rangeX.second; i++) {
            for (int j = rangeY.first; j <= rangeY.second; j++) {
                map.emplace(std::make_pair(i, j), target);
            }
        }
    }

    void clear() {
        map.clear();
    }

    std::vector<std::pair<std::pair<int, int>, std::vector<Entities::Entity*>>> detectCollisions() {
        console->info("Detecting collisions");
        console->info("Map size: {}", map.size());

        std::vector<std::pair<std::pair<int, int>, std::vector<Entities::Entity*>>> total_collisions;
        std::set<std::pair<int, int>> processed_keys; // To keep track of processed keys

        for (auto it = map.begin(); it != map.end(); ) {
            auto key = it->first;
            if (processed_keys.find(key) != processed_keys.end()) {
                ++it; // Skip already processed keys
                continue;
            }

            auto range = map.equal_range(key);
            std::vector<Entities::Entity*> collision_entities;

            for (auto range_it = range.first; range_it != range.second; ++range_it) {
                collision_entities.push_back(range_it->second);
            }

            if (collision_entities.size() > 1) {
                console->info("Collision at: {{{}, {}}}. Between {} elements.", key.first, key.second, collision_entities.size());
                total_collisions.push_back(std::make_pair(key, collision_entities));
            }

            processed_keys.insert(key);
            it = range.second; // Move iterator to the end of the current range
        }

        console->debug("Done detecting collisions");
        return total_collisions;
    }

    // fist is left/right walls, second for top/bottom
    std::pair<std::set<Entities::Entity*>, std::set<Entities::Entity*>> isOutsideWindow() {
        sf::FloatRect windowRect(0, 0, windowWidth, windowHeight);
        std::set<Entities::Entity*> top_bottom;
        std::set<Entities::Entity*> right_left;

         for (const auto& entry : map) {
            const auto& cell = entry.first;
            Entities::Entity* entity = entry.second;
            auto bounds = entity->getBounds();

            if (cell.first == 0 || cell.first == cols - 1 || cell.second == 0 || cell.second == rows - 1) {
                checkBounds(bounds, windowRect, top_bottom, right_left, entity);
            }
        }

        return std::make_pair(right_left, top_bottom);
    }

    std::size_t size() const {
        return map.size();
    }

};