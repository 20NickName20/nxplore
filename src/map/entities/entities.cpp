#pragma once
#include "entities.h"
#include "../../io/color.h"
#include <array>
#include <string_view>
#include <atomic>

namespace Entities {

struct EntityInfo {
    EntityKind kind;
    const char* visual;
    short baseColor;
};

// --- Static compile-time definitions ---
constexpr std::array<EntityInfo, 2> ENTITY_DEFS{{
    { EntityKind::Player,   " @", Color::pairId(COLOR_MAGENTA, COLOR_BLACK) },
    { EntityKind::Skeleton, " k", Color::defaultPair() },
}};

// --- Accessor for definition ---
constexpr const EntityInfo& getEntityInfo(EntityKind kind) {
    for (auto& e : ENTITY_DEFS)
        if (e.kind == kind)
            return e;
    return ENTITY_DEFS.front(); // fallback
}

// --- Visuals ---
constexpr const char* getVisual(const Entity& e) {
    const auto& def = getEntityInfo(e.kind);

    return def.visual;
}

// --- Colors ---
constexpr short getColorPair(const Entity& e) {
    const auto& def = getEntityInfo(e.kind);

    return def.baseColor;
}

} // namespace Entities
