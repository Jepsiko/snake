

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP


#include <vector>
#include "../Position.hpp"
#include <array>

class Snake {
private:
    Position* head;
    std::vector<Position*> tail;
    int length;
    Position* direction;
    Position* tmpDirection;

    unsigned char r;
    unsigned char g;
    unsigned char b;

    void changeDirection();

public:
    Snake(Position* startPos);

    bool move();

    void grow();

    bool onSnake(Position* position) const;

    // Mutators
    const Position* getPosition() const;

    const std::vector<Position*>& getTail() const;

    void setTmpDirection(const Position* direction);

    const Position* getDirection() const;

    int getLength() const;

    // Color
    unsigned char getR() const;

    unsigned char getG() const;

    unsigned char getB() const;
};


#endif //SNAKE_SNAKE_HPP
