

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "GameGUI.hpp"
#include "../Abstract/AbstractManager.hpp"

class Game : public AbstractManager {
private:
    GameUI *gameUI;

public:
    Game();

    void run() override;
};


#endif //SNAKE_GAME_HPP
