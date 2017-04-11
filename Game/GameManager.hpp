

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "../Abstract/AbstractManager.hpp"

class GameUI;

class GameManager : public AbstractManager {
private:
    GameUI *gameUI;

public:
    GameManager();

    void run() override;
};


#endif //SNAKE_GAME_HPP
