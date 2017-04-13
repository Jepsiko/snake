

#include "Snake.hpp"
#include "../Tools/Constants.hpp"
#include <algorithm>

Snake::Snake(Position *startPos) {
    length = INITIAL_LENGTH;
    head = startPos;
    direction = new Position(1, 0);
    tmpDirection = new Position(1, 0);
}

bool Snake::move() {
    changeDirection();
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
        if (tail.size() > length) tail.erase(tail.begin());
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

void Snake::changeDirection() {
    this->direction = new Position(tmpDirection->x, tmpDirection->y);
}

void Snake::grow() {
    length++;
}

bool Snake::onSnake(Position *position) {
    bool isOnSnake = false;

    if (*head == *position) isOnSnake = true;
    else {
        for (auto pos : tail) {
            logFile << pos->to_string().c_str();
            if (not isOnSnake) {
                if (*pos == *position) {
                    isOnSnake = true;
                }
            }
        }
    }

    return isOnSnake;
}

void Snake::setTmpDirection(const Position *direction) {
    if (*(*direction + *this->direction) == Position()) return; // If it's an opposite direction
    this->tmpDirection = new Position(direction->x, direction->y);
}
