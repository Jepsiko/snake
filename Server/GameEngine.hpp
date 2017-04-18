

#ifndef SNAKE_GAMEENGINE_HPP
#define SNAKE_GAMEENGINE_HPP


#include "../Common/Entities/Snake.hpp"
#include "../Common/Entities/Food.hpp"
#include "../Common/Tools/Constants.hpp"

class GameEngine {
private:
    unsigned long id;
    std::vector<Snake*> snakes;
    std::vector<Food*> food;

    int stepCount;

    void spawnFood();

    void deleteFood(Position* position);

public:
    void run();

    void handleDirection(char direction);

    bool play();
};


#endif //SNAKE_GAMEENGINE_HPP
