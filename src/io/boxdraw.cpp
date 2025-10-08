#pragma once
#include <ncurses.h>
#include "boxdraw.h"

namespace BoxDraw {

void drawBox(int x, int y, int w, int h, const BorderChars& border) {
    // Horizontal lines
    for (int i = 1; i < w - 1; ++i) {
        mvprintw(y,     x + i, border.top);
        mvprintw(y+h-1, x + i, border.bottom);
    }

    // Vertical lines
    for (int i = 1; i < h - 1; ++i) {
        mvprintw(y + i, x,       border.left);
        mvprintw(y + i, x + w-1, border.right);
    }

    // Corners
    mvprintw(y,     x,     border.topLeft);
    mvprintw(y,     x+w-1, border.topRight);
    mvprintw(y+h-1, x,     border.bottomLeft);
    mvprintw(y+h-1, x+w-1, border.bottomRight);
}

} // namespace BoxDraw
