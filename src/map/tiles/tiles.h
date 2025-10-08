#pragma once

#include <optional>

namespace Tiles {

enum class TileKind {
    None,

    Grass,
    Floor,
    Sand,
    
    Door,

    BrickWall,
    BrickFloor,
    
    RockWall,
    RockFloor,
    
    StairsUp,
    StairsDown,
    
    Pit,
    Water,
    Lava,

    Rock,
    Tree,
    Ice
};

struct Tile {
    TileKind kind;
    std::optional<int> targetMapId;
    std::optional<bool> isOpen;
};

}