

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP


#include <vector>
#include "../Position.hpp"

class Snake {
private:
    Position* head;
    std::vector<Position*> tail;
    int lenght;
    Position* direction;

public:
    Snake(Position* startPos);

    bool move();

    void grow();

    bool onSnake(Position* position);

    const Position* getPosition() const;

    const std::vector<Position*>& getTail() const;

    void setDirection(const Position* direction);
};


#endif //SNAKE_SNAKE_HPP
