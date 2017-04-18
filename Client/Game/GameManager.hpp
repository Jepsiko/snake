

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "../Abstract/AbstractManager.hpp"
#include "../../Common/Entities/Snake.hpp"
#include "../../Common/Entities/Food.hpp"

class GameUI;

class GameManager : public AbstractManager {
private:
    GameUI *gameUI;
    unsigned long id;
    std::vector<Snake*> snakes;
    std::vector<Food*> food;

    bool gameOver;
    int stepCount;

    void spawnFood();

    void deleteFood(Position* position);

public:
    GameManager();

    void run() override;

    void handleDirection(char direction);

    bool play();
};


#endif //SNAKE_GAME_HPP
