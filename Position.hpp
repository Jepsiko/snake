

#ifndef SNAKE_POSITION_HPP
#define SNAKE_POSITION_HPP


#include <iosfwd>
#include <string>

class Position {
public:
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    std::string to_string() const { return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }

    Position operator+(const Position& other) {
        return Position(this->x + other.x, this->y + other.y);
    }
};

#endif //SNAKE_POSITION_HPP
