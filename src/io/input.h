#pragma once
#include <string>

#define KEY_SHIFT_UP 337
#define KEY_SHIFT_DOWN 336
#define KEY_SHIFT_LEFT 393
#define KEY_SHIFT_RIGHT 402

namespace Input {

struct Key {
    char ch = ' ';
    int code = ERR;
    bool isCtrl = false;
    bool isAlt = false;
    bool isSpecial = false;
};

Key readKey();
Key readLastKey();
std::string keyToString(const Key& key);

} // namespace Input
