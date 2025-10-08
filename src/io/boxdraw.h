#pragma once
#include <ncurses.h>
#include <string>

namespace BoxDraw {

struct BorderChars {
    const char* top;
    const char* bottom;
    const char* left;
    const char* right;

    const char* topLeft;
    const char* topRight;
    const char* bottomLeft;
    const char* bottomRight;
};

namespace Style {
    BorderChars LIGHT  = {"─", "─", "│", "│", "┌", "┐", "└", "┘"};
    BorderChars HEAVY  = {"━", "━", "┃", "┃", "┏", "┓", "┗", "┛"};
    BorderChars DOUBLE = {"═", "═", "║", "║", "╔", "╗", "╚", "╝"};
    BorderChars KEY    = {"─", "═", "│", "│", "┌", "┐", "╘", "╛"};
}

void drawBox(int x, int y, int w, int h, const BorderChars& border);

} // namespace BoxDraw
