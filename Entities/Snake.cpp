

#include "Snake.hpp"
#include <algorithm>

Snake::Snake(Position *startPos) {
    head = startPos;
    direction = new Position(1, 0);
}

bool Snake::move() {
    bool dead = false;

    printf("Head : ");
    printf(head->to_string().c_str());
    printf("\nDirection : ");
    printf(direction->to_string().c_str());
    printf("\nNext Pos : ");
    Position* nextPos = *direction + *head;
    printf(nextPos->to_string().c_str());
    printf("\nTail : ");
    for (auto pos : tail) {
        printf(pos->to_string().c_str());
        if (not dead and *pos == *nextPos) dead = true;
    }
    printf("\n\n");

    if (not dead) {
        tail.push_back(head);
        //tail.erase(tail.begin());
        head = nextPos;
    }

    return dead;
}

const Position *Snake::getPosition() const {
    return head;
}

const std::vector<Position *> &Snake::getTail() const {
    return tail;
}

void Snake::setDirection(const Position *direction) {
    this->direction = new Position(direction->x, direction->y);
}
