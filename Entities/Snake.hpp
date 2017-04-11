

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP


#include <vector>
#include "../Position.hpp"

class Snake {
private:
    Position* head;
    std::vector<Position*> tail;
    Position* direction;

public:
    Snake(Position* startPos = new Position());

    bool move(const Position* direction);

    bool move();

    const Position* getPosition() const;
};


#endif //SNAKE_SNAKE_HPP
