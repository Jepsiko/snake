

#include "Snake.hpp"
#include <algorithm>

Snake::Snake(Position *startPos) {
    lenght = 5;
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
        if (tail.size() > lenght) tail.erase(tail.begin());
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
    if (*(*this->direction + *direction) == Position()) return; // If it's an opposite direction
    this->direction = new Position(direction->x, direction->y);
}

void Snake::grow() {
    lenght++;
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
