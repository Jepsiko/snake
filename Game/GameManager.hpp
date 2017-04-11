

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "GameGUI.hpp"
#include "../Abstract/AbstractManager.hpp"

class Game : public AbstractManager {
private:
    GameGUI *gameGUI;

public:
    Game();

    void run();
};


#endif //SNAKE_GAME_HPP
