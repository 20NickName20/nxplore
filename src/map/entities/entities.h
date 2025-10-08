#pragma once
#include <string>
#include <optional>
#include "../../util/vec2.h"

namespace Entities {

enum class EntityKind {
    Player,
    Skeleton
};

enum class Action {
    Move,
    Shoot
};

struct Entity {
    int id;
    EntityKind kind;
    Vec2 pos;
    Vec2 dir;
    Action action;
    int health;
    bool markedForRemoval;
    std::optional<std::string> name;
};

} // namespace Entities
