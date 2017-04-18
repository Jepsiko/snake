
#include <cstring>
#include "../Common/Tools/Global.hpp"
#include "Game/GameManager.hpp"

int main(int argc, char **argv) {

    if (argc == 2) {
        if (strcmp(argv[1], "-c") == 0 or strcmp(argv[1], "--console") == 0) {
            isConsole = true;
        }
    }

    GameManager* game = new GameManager();
    game->run();

    return 0;
}