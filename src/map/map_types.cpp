#pragma once
#include "map_types.h"
#include "../util/vec2.h"

namespace Maps {
    namespace Types {
        Vec2 getSize(Type type) {
            switch (type)
            {
            case Type::Crossroad:
                {
                    int x = rand() % 30 + 10;
                    return Vec2(x, x);
                }
            
            default:
                {
                    int x = rand() % 30 + 10;
                    int y = rand() % 30 + 10;
                    return Vec2(x, y);
                }
            }
        }
    }
}