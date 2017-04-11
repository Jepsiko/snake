

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "../Abstract/AbstractManager.hpp"
#include "../Entities/Snake.hpp"

class GameUI;

class GameManager : public AbstractManager {
private:
    GameUI *gameUI;
    Snake *snake;
    bool gameOver;

public:
    GameManager();

    void run() override;

    void handleDirection(char direction);

    bool isGameOver();
};


#endif //SNAKE_GAME_HPP
