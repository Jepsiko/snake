

#include "Snake.hpp"
#include "../Tools/Global.hpp"
#include <algorithm>

Snake::Snake(Position *startPos) {
    head = startPos;
    direction = new Position(1, 0);
}

bool Snake::move() {
    bool dead = false;

    logFile << "Head : " << head->to_string().c_str();

    logFile << "\nDirection : " << direction->to_string().c_str();

    Position* nextPos = *direction + *head;
    logFile << "\nNext Pos : " << nextPos->to_string().c_str();

    logFile << "\nTail : ";
    for (auto pos : tail) {
        logFile << pos->to_string().c_str();
        if (not dead) {
            if (*pos == *nextPos) {
                dead = true;
            }
        }
    }
    logFile << "\n";

    if (dead) logFile << "\nDEAD";
    else {
        tail.push_back(head);
        //tail.erase(tail.begin());
        head = nextPos;
    }

    logFile << "\n";

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
