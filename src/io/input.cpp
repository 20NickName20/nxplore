#pragma once
#include "input.h"
#include <ncurses.h>

namespace Input {

Key readKey() {
    int code = getch();
    Key key;
    key.code = code;
    if (code == ERR) {
        return key;
    }
    if (code == 27) {
        key.isAlt = true;
        code = getch();
        if (code == ERR) {
            return key;
        }
    }

    // Special cases
    if (code == '\n' || code == KEY_ENTER) {
        key.code = KEY_ENTER;
        key.isSpecial = true;
        return key;
    }
    if (code == '\t') {
        key.ch = '\t';
        key.isSpecial = true;
        return key;
    }

    // Handle Ctrl combos (ASCII 1–26)
    if (code >= 1 && code <= 26) {
        key.ch = 'A' + (code - 1);
        key.isCtrl = true;
        return key;
    }
    // Printable ASCII
    if (code >= 32 && code < 127) {
        key.ch = code;
        return key;
    }

    key.isSpecial = true;
    return key;
}

Key readLastKey() {
    Key key, valid;
    valid = readKey();
    while ((key = readKey()).code != ERR) {
        valid = key;
    }
    return valid;
}

std::string keyToString(const Key& key) {
    if (key.isCtrl) {
        return "Ctrl+" + std::string(1, key.ch);
    }
    if (key.isSpecial) {
        switch (key.code) {
            case 27: return "ESC";
            case KEY_UP: return "Arrow Up";
            case KEY_DOWN: return "Arrow Down";
            case KEY_LEFT: return "Arrow Left";
            case KEY_RIGHT: return "Arrow Right";
            case KEY_SHIFT_UP: return "Shift+Arrow Up";
            case KEY_SHIFT_DOWN: return "Shift+Arrow Down";
            case KEY_SHIFT_LEFT: return "Shift+Arrow Left";
            case KEY_SHIFT_RIGHT: return "Shift+Arrow Right";
            case KEY_BACKSPACE: return "Backspace";
            case KEY_DC: return "Delete";
            case KEY_HOME: return "Home";
            case KEY_END: return "End";
            case KEY_PPAGE: return "Page Up";
            case KEY_NPAGE: return "Page Down";
            case '\t': return "Tab";
            case 353: return "Backtab";
            case KEY_ENTER: return "Enter";
            case KEY_RESIZE: return "Terminal Resize";
            default:
                if (key.code >= KEY_F(1) && key.code <= KEY_F(12)) {
                    return "F" + std::to_string(key.code - KEY_F(0));
                }
                return "Unknown(" + std::to_string(key.code) + ")";
        }
    }
    if (key.isAlt) {
        return "Alt+" + std::string(1, key.ch);
    }
    return std::string(1, key.ch);
}

} // namespace Input
