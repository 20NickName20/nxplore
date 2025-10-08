#pragma once

#include <optional>

namespace Tiles {

enum class TileKind {
    Wall,
    Floor,
    Door,
    StairsUp,
    StairsDown,
    Grass,
    Pit,
    Rock,
    Water,
    Lava,
    Tree,
    Ice,
    Sand
};

struct Tile {
    TileKind kind;
    std::optional<int> targetMapId;
    std::optional<bool> isOpen;
};

}