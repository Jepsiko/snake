

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "../Abstract/AbstractManager.hpp"
#include "../Entities/Snake.hpp"
#include "../Entities/Food.hpp"

class GameUI;

class GameManager : public AbstractManager {
private:
    GameUI *gameUI;
    Snake *snake;
    bool gameOver;
    std::vector<Food*> food;

    void spawnFood();

    void deleteFood(Position* position);

public:
    GameManager();

    void run() override;

    void handleDirection(char direction);

    bool play();
};


#endif //SNAKE_GAME_HPP
