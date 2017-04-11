

#include "Snake.hpp"

bool Snake::move(const Position *direction) {
    return false;
}

Snake::Snake(Position *startPos = new Position()) {
    head = startPos;
}
