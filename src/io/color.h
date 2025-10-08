#pragma once
#include <array>
#include <ncurses.h>

namespace Color {

struct RGB {
    short r, g, b; // 0–1000
    constexpr RGB(short r, short g, short b) : r(r), g(g), b(b) {}
};

struct ColorDef {
    short id;
    RGB rgb;
};

struct Pair {
    short id;
    short fg;
    short bg;
};

constexpr std::array<ColorDef, 5> CUSTOM_COLORS {{
    #define COLOR_BLUE_GRAY 16
    ColorDef{COLOR_BLUE_GRAY, {400, 400, 600}},
    #define COLOR_DARK_GRAY 17
    ColorDef{COLOR_DARK_GRAY, {100, 100, 100}},
    #define COLOR_DARK_DARK_GRAY 18
    ColorDef{COLOR_DARK_DARK_GRAY, {1, 1, 1}},
    #define COLOR_LIGHT_BROWN 19
    ColorDef{COLOR_LIGHT_BROWN, {546, 355, 207}},
    #define COLOR_DARK_BROWN 20
    ColorDef{COLOR_DARK_BROWN, {367, 187, 46}},
}};

constexpr std::array<Pair, 12> PAIRS {{
    {1, COLOR_RED, COLOR_BLACK},
    {2, COLOR_GREEN, COLOR_BLACK},
    {3, COLOR_WHITE, COLOR_BLUE},
    {4, COLOR_WHITE, COLOR_RED},
    {5, COLOR_MAGENTA, COLOR_BLACK},
    {6, COLOR_WHITE, COLOR_BLUE_GRAY},
    {7, COLOR_BLUE_GRAY, COLOR_BLACK},
    {8, COLOR_WHITE, COLOR_LIGHT_BROWN},
    {9, COLOR_LIGHT_BROWN, COLOR_BLACK},
    {10, COLOR_DARK_BROWN, COLOR_BLACK},
    {11, COLOR_YELLOW, COLOR_BLACK},
    {12, COLOR_DARK_DARK_GRAY, COLOR_DARK_GRAY},
}};

// Lookup function (constexpr)
constexpr short pairId(short fg, short bg) {
    for (auto& p : PAIRS) {
        if (p.fg == fg && p.bg == bg)
            return p.id;
    }
    return 0; // default (no match)
}

constexpr short defaultPair() {
    return 0;
}

// Runtime init
inline void initDefaults() {
    for (auto& c : CUSTOM_COLORS) {
        init_color(c.id, c.rgb.r, c.rgb.g, c.rgb.b);
    }
    for (auto& p : PAIRS) {
        init_pair(p.id, p.fg, p.bg);
    }
}

} // namespace Color
