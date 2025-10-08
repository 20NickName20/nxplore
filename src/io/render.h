#pragma once
#include <ncurses.h>
#include "../map/map.h"
#include "../map/tiles/tiles.h"
#include "../io/color.h"

namespace Render {

void init();                     // initializes ncurses & colors
void shutdown();                 // restores terminal
void clearScreen();              // clears frame
void drawMap(const Maps::Map& map, const Vec2& camPos, const Vec2& camSize);
void drawTile(int screenX, int screenY, const Tiles::Tile& tile);
void refreshScreen();            // call at end of frame

} // namespace Render
