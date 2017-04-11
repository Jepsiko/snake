

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "GameGUI.hpp"

class Game {
private:
    GameGUI *gameGUI;

public:
    Game();

    void run();
};


#endif //SNAKE_GAME_HPP
