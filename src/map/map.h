#pragma once
#include <vector>
#include <unordered_map>
#include <optional>
#include "tiles/tiles.h"
#include "entities/entities.h"
#include "../util/vec2.h"

namespace Maps {

class Map {
public:
    Map(int width, int height);

    Map(int width, int height, const Tiles::TileKind &t);

    // Basic accessors
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Tile access
    Tiles::Tile& at(int x, int y);
    const Tiles::Tile& at(int x, int y) const;
    bool isPassable(int x, int y) const;

    // Utility: fill map with a tile type
    void fill(const Tiles::TileKind& t);
    void fill(const Tiles::TileKind& t, int x, int y, int width, int height);

    // Entity management
    int nextEntityId();
    Entities::Entity& spawnEntity(Entities::EntityKind kind, Vec2 pos, int health);
    void updateEntities();
    std::unordered_map<int, Entities::Entity>& getEntities();
    const std::unordered_map<int, Entities::Entity>& getEntities() const;

    // Generation
    Vec2 generate(std::optional<Vec2> returnPos, std::optional<Tiles::TileKind> returnType);

private:
    int width;
    int height;
    int entityIdCounter = 1;

    std::vector<Tiles::Tile> tiles;
    std::unordered_map<int, Entities::Entity> entities;
};

} // namespace Maps