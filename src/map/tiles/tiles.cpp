#pragma once
#include "tiles.h"
#include "../../io/color.h"
#include <array>
#include <string_view>

namespace Tiles {

struct TileInfo {
    TileKind kind;
    const char* visual;
    short baseColor;
    bool basePassable;
};

constexpr std::array<TileInfo, 14> TILE_DEFS{{
    { TileKind::Water, ",~", Color::pairId(COLOR_WHITE, COLOR_BLUE), false },
    { TileKind::Lava, "/~", Color::pairId(COLOR_WHITE, COLOR_RED), false },
    { TileKind::Tree, " 4", Color::pairId(COLOR_GREEN, COLOR_BLACK), false },
    { TileKind::Ice, "/]", Color::pairId(COLOR_BLUE, COLOR_BLACK), false },
    { TileKind::Sand, "..", Color::pairId(COLOR_YELLOW, COLOR_BLACK), true },
    { TileKind::Rock, " O", Color::defaultPair(), false },
    { TileKind::Wall, "##", Color::pairId(COLOR_WHITE, COLOR_BLUE_GRAY), false },
    { TileKind::Door, " +", Color::defaultPair(), true },
    { TileKind::Floor, "  ", Color::defaultPair(), true },
    { TileKind::Grass, "',", Color::pairId(COLOR_GREEN, COLOR_BLACK), true },
    { TileKind::Pit, " v", Color::pairId(COLOR_DARK_DARK_GRAY, COLOR_DARK_GRAY), false },
    { TileKind::StairsUp, " <", Color::defaultPair(), true },
    { TileKind::StairsDown, " >", Color::defaultPair(), true },
}};

constexpr const TileInfo& getTileInfo(TileKind kind) {
    for (auto& t : TILE_DEFS)
        if (t.kind == kind)
            return t;
    return TILE_DEFS.front(); // fallback
}

bool isPassable(const Tile& tile) {
    const auto& def = getTileInfo(tile.kind);
    if (tile.kind == TileKind::Door)
        return tile.isOpen.value_or(false);
    return def.basePassable;
}

const char* getVisual(const Tile& tile) {
    const auto& def = getTileInfo(tile.kind);

    switch (tile.kind) {
    case TileKind::Door:
        return (tile.isOpen.value_or(false) ? " ." : def.visual);

    default:
        return def.visual;
    }
}

short getColorPair(const Tile& tile) {
    const auto& def = getTileInfo(tile.kind);

    switch (tile.kind) {
    /*
    case TileKind::Water:
        // deeper water (higher data) -> darker blue
        return (tile.data > 3)
            ? Color::pairId(COLOR_BLUE, COLOR_BLACK)
            : def.baseColor;

    case TileKind::Lava:
        // cooler lava -> yellow tint
        return (tile.data < 2)
            ? Color::pairId(COLOR_YELLOW, COLOR_RED)
            : def.baseColor;
    */

    default:
        return def.baseColor;
    }
}

} // namespace Tiles
