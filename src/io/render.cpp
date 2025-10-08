#pragma once
#include <locale.h>
#include <algorithm>
#include "../util/vec2.h"
#include "render.h"
#include "../map/tiles/tiles.h"
#include "../map/tiles/tiles.cpp"
#include "../map/entities/entities.h"
#include "../map/entities/entities.cpp"
#include "../io/input.cpp"

namespace Render {

bool testForColors() {
    if (!has_colors()) return false;
    if (!can_change_color()) return false;
    return true;
}

void exitWithMessage(const char* msg, int status) {
    nodelay(stdscr, FALSE);
    mvprintw(1, 2, msg);
    mvprintw(2, 2, "Press any key to exit...");

    Input::readKey();
    endwin();
    exit(status);
}

void init() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    meta(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    start_color();

    if (!testForColors()) {
        exitWithMessage("Your terminal doesn't support important stuff", 1);
    }

    Color::initDefaults();
}

void shutdown() {
    endwin();
}

void clearScreen() {
    erase();
}

void refreshScreen() {
    refresh();
}

void drawTile(int screenX, int screenY, const Tiles::Tile& tile) {
    const auto vis = Tiles::getVisual(tile);
    const short color = Tiles::getColorPair(tile);

    attron(COLOR_PAIR(color));
    mvprintw(screenY, screenX * 2, vis);
    attroff(COLOR_PAIR(color));
}

void drawEntity(int screenX, int screenY, const Entities::Entity& entity) {
    const auto vis = Entities::getVisual(entity);
    const short color = Entities::getColorPair(entity);

    attron(COLOR_PAIR(color));
    mvprintw(screenY, screenX * 2, vis);
    attroff(COLOR_PAIR(color));
}

void drawMap(const Maps::Map& map, const Vec2& camPos, const Vec2& camSize) {
    const int w = map.getWidth();
    const int h = map.getHeight();

    Vec2 camSizeHalf = camSize / 2;

    // Clamp camera to map bounds
    int startX = std::clamp(camPos.x - camSizeHalf.x, 0, std::max(0, w - camSize.x));
    int startY = std::clamp(camPos.y - camSizeHalf.y, 0, std::max(0, h - camSize.y));

    int endX = std::min(startX + camSize.x, w);
    int endY = std::min(startY + camSize.y, h);

    // --- Draw tiles first ---
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            const auto& tile = map.at(x, y);
            drawTile(x - startX, y - startY, tile);
        }
    }

    // --- Draw entities on top ---
    for (const auto& e : map.getEntities()) {
        // Skip if entity is outside camera view
        if (e.second.pos.x < startX || e.second.pos.x >= endX || e.second.pos.y < startY || e.second.pos.y >= endY)
            continue;

        const int screenX = e.second.pos.x - startX;
        const int screenY = e.second.pos.y - startY;

        drawEntity(screenX, screenY, e.second);
    }
}

} // namespace Render
