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

    Ice,
    IceWall,
    Snow,
    
    StairsUp,
    StairsDown,
    
    Pit,
    Water,
    Lava,

    Rock,
    Tree
};

struct Tile {
    TileKind kind;
    std::optional<int> targetMapId;
    std::optional<bool> isOpen;
};

}