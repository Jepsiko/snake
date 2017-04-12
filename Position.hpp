

#ifndef SNAKE_POSITION_HPP
#define SNAKE_POSITION_HPP


#include <iosfwd>
#include <string>
#include "Tools/Global.hpp"

class Position {
public:
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    std::string to_string() const { return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }

    bool operator==(const Position& other) {
        return this->x == other.x and this->y == other.y;
    }

    friend Position* operator+(const Position& a, const Position& b) {
        return new Position(a.x + b.x, a.y + b.y);
    }
};

#endif //SNAKE_POSITION_HPP
