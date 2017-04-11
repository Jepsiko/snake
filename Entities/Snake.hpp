

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP


#include <vector>
#include "../Position.hpp"

class Snake {
private:
    Position* head;
    std::vector<Position*> tail;

public:
    Snake(Position* startPos);

    bool move(const Position* direction);
};


#endif //SNAKE_SNAKE_HPP
