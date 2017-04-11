

#include "Snake.hpp"

bool Snake::move(const Position *direction) {
    return false;
}

Snake::Snake(Position *startPos) {
    head = startPos;
    direction = new Position(1, 0);
}

bool Snake::move() {
    return move(direction);
}

const Position *Snake::getPosition() const {
    return head;
}
