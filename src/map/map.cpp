#include <vector>
#include "map.h"
#include "tiles/tiles.h"
#include "tiles/tiles.cpp"
#include "entities/entities.h"
#include "entities/entities.cpp"
#include <algorithm>

namespace Maps {

Map::Map(int width, int height)
    : width(width), height(height), tiles(width * height) {
}
Map::Map(int width, int height, const Tiles::TileKind& t)
    : width(width), height(height), tiles(width * height, Tiles::Tile{t}) {
}

int Map::nextEntityId() {
    return entityIdCounter++;
}

Entities::Entity& Map::spawnEntity(Entities::EntityKind kind, Vec2 pos, int health) {
    int id = nextEntityId();
    Entities::Entity e;
    e.id = id;
    e.kind = kind;
    e.action = Entities::Action::Move;
    e.pos = pos;
    e.health = health;
    e.markedForRemoval = false;

    Entities::Entity& ref = entities.emplace(id, std::move(e)).first->second;
    return ref;
}

std::unordered_map<int, Entities::Entity>& Map::getEntities() {
    return entities;
}

const std::unordered_map<int, Entities::Entity>& Map::getEntities() const {
    return entities;
}

void Map::updateEntities() {
    for (auto& entry : entities) {
        Entities::Entity& entity = entry.second;
        Vec2 newPos = entity.pos + entity.dir;
        switch (entity.kind) {
        case Entities::EntityKind::Player:
            {
                if (entity.action == Entities::Action::Move) {
                    if (isPassable(newPos.x, newPos.y)) {
                        entity.pos = newPos;
                    }
                    entity.dir = Vec2::zero();
                }
            }
            break;

        case Entities::EntityKind::Skeleton:
            break;

        default:
            break;
        }
    }
}

Tiles::Tile& Map::at(int x, int y) {
    return tiles[y * width + x];
}

const Tiles::Tile& Map::at(int x, int y) const {
    return tiles[y * width + x];
}

bool Map::isPassable(int x, int y) const {
    return Tiles::isPassable(at(x, y));
}

void Map::fill(const Tiles::TileKind& t) {
    for (auto& tile : tiles) {
        tile = Tiles::Tile{t};
    }
}

void Map::fill(const Tiles::TileKind& t, int x, int y, int w, int h) {
    w += x;
    h += y;
    for (int x1 = x; x1 < w; x1++) {
        for (int y1 = y; y1 < h; y1++) {
            at(x1, y1).kind = t;
        }
    }
}

Vec2 Map::generate(std::optional<Vec2> returnPos, std::optional<Tiles::TileKind> returnType) {
    fill(Tiles::TileKind::Wall);
    std::vector<Vec2> spawnPositions;
    spawnPositions.reserve(width * height);
    for (int x = 1; x < width - 1; x++) {
        for (int y = 1; y < height - 1; y++) {
            Vec2 pos = Vec2(x, y);
            Tiles::Tile& tile = at(x, y);
            
            Vec2 rounded = Vec2(x / 8 * 8 + 4, y / 8 * 8 + 4);
            int dist = (pos - rounded).smallestSquare();
            
            if (dist < 2) {
                tile.kind = Tiles::TileKind::Pit;
                continue;
            }
            if (dist < (3 + (x + y) % 3)) {
                tile.kind = Tiles::TileKind::Sand;
                continue;
            }

            if (rand() % 20 == 0) {
                spawnEntity(Entities::EntityKind::Skeleton, pos, 40);
            }

            spawnPositions.push_back(pos);

            tile.kind = Tiles::TileKind::Floor;
        }
    }
    
    int spawnOptions = spawnPositions.size();
    if (!spawnOptions) {
        return Vec2();
    }

    Vec2 spawnPos = spawnPositions[rand() % spawnOptions];
    return Vec2(spawnPos.x, spawnPos.y);
}

} // namespace Maps