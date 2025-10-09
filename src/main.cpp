#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <optional>

#include "io/boxdraw.h"
#include "io/boxdraw.cpp"

#include "io/render.h"
#include "io/render.cpp"

#include "io/input.h"
#include "io/input.cpp"

#include "map/entities/entities.h"
#include "map/entities/entities.cpp"

#include "map/tiles/tiles.h"
#include "map/tiles/tiles.cpp"

#include "map/map.h"
#include "map/map.cpp"

int main() {
    srand(time(nullptr));

    Maps::Types::Type mapType = Maps::Types::Type::IceCave;
    Maps::Map map = Maps::createMap(mapType);
    Vec2 spawnPos = map.generate(std::nullopt, std::nullopt);
    
    auto& player = map.spawnEntity(Entities::EntityKind::Player, spawnPos, 100);
    
    Input::Key key;
    Input::Key lastKey;

    Vec2 camSize = {40, 20};

    Render::init();
    while (true) {
        player.action = Entities::Action::Move;

        key = Input::readLastKey();

        if (key.code != ERR) {
            lastKey = key;
        }

        if (key.isCtrl && key.ch == 'Q') {
            break;
        }

        if (key.isSpecial) {
            switch (key.code)
            {
            case KEY_UP:
                player.dir = Vec2::up();
                break;
            case KEY_LEFT:
                player.dir = Vec2::left();
                break;
            case KEY_DOWN:
                player.dir = Vec2::down();
                break;
            case KEY_RIGHT:
                player.dir = Vec2::right();
                break;

            default:
                break;
            }
        }

        map.updateEntities();

        Render::clearScreen();

        Render::drawMap(map, player.pos, camSize);
        BoxDraw::drawBox(4, camSize.y + 1, 5, 3, BoxDraw::Style::KEY);
        mvprintw(camSize.y + 2, 6, Input::keyToString(lastKey).c_str());

        Render::refreshScreen();
        
        usleep(100000);
    }

    Render::shutdown();
    return 0;
}
