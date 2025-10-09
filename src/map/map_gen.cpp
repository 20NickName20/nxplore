#pragma once
#include <optional>
#include <vector>
#include "map.h"
#include "map_types.h"
#include "tiles/tiles.h"
#include "tiles/tiles.cpp"
#include "../util/vec2.h"

namespace Maps {

namespace Gen {
Vec2 generateCave(Map* map, std::optional<Vec2> returnPos, std::optional<Tiles::TileKind> returnType, const Tiles::TileKind wallKind, const Tiles::TileKind floorKind, const int smoothing, const int thereshold) {
    std::vector<Vec2> spawnPositions;
    int width = map->getWidth();
    int height = map->getHeight();
    
    std::vector<Tiles::TileKind> genMap(width * height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (x == 0 || y == 0 || x == (width - 1) || y == (height - 1)) {
                genMap[y * width + x] = wallKind;
                continue;
            }

            if (rand() % 2) {
                genMap[y * width + x] = floorKind;
            } else {
                genMap[y * width + x] = wallKind;
            }
        }
    }

    for (int i = 0; i < smoothing; i++) {
        std::vector<Tiles::TileKind> smoothedMap(width * height, wallKind);
        for (int x = 1; x < width - 1; x++) {
            for (int y = 1; y < height - 1; y++) {
                int wallCount = 0;
                for (int dx = x - 1; dx <= x + 1; dx++) {
                    for (int dy = y - 1; dy <= y + 1; dy++) {
                        if (genMap[dy * width + dx] == wallKind) {
                            wallCount++;
                        }
                    }
                }
                if (wallCount > (thereshold + rand() % 2)) {
                    smoothedMap[y * width + x] = wallKind;
                } else {
                    smoothedMap[y * width + x] = floorKind;
                }
            }
        }

        genMap = smoothedMap;
    }
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Vec2 pos = Vec2(x, y);
            Tiles::Tile& tile = map->at(x, y);
            tile.kind = genMap[y * width + x];
            if (Tiles::isPassable(tile)) {
                spawnPositions.push_back(pos);
            }
        }
    }

    int spawnOptions = spawnPositions.size();
    if (!spawnOptions) {
        return Vec2();
    }

    Vec2 spawnPos = spawnPositions[rand() % spawnOptions];
    return Vec2(spawnPos.x, spawnPos.y);
}

Vec2 generate(Map* map, std::optional<Vec2> returnPos, std::optional<Tiles::TileKind> returnType) {
    switch (map->getType())
    {
    case Types::Type::RockCave:
        return generateCave(map, returnPos, returnType, Tiles::TileKind::RockWall, Tiles::TileKind::RockFloor, 1, 4);
    case Types::Type::IceCave:
        return generateCave(map, returnPos, returnType, Tiles::TileKind::IceWall, Tiles::TileKind::Snow, 1, 4);
    
    default:
        return Vec2();
    }
}

}

}