

#include "Snake.hpp"
#include "../Tools/Constants.hpp"
#include <algorithm>

Snake::Snake(Position *startPos) {
    srand((unsigned) time(0));
    length = INITIAL_LENGTH;
    head = startPos;
    direction = new Position(1, 0);
    tmpDirection = new Position(1, 0);
    r = (unsigned char) ((unsigned char) rand() % 0x60);
    g = (unsigned char) ((unsigned char) rand() % 0x90);
    b = (unsigned char) rand();
}

bool Snake::move() {
    changeDirection();
    bool dead = false;

    Position* nextPos = *direction + *head;
    for (unsigned long i = tail.size(); i-- > 0; ) {
        if (i >= INITIAL_LENGTH && not dead && *tail.at(i) == *nextPos) {
            dead = true;
        }
    }

    if (not dead) {
        tail.push_back(head);
        if (tail.size() > length) tail.erase(tail.begin());
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

void Snake::changeDirection() {
    this->direction = new Position(tmpDirection->x, tmpDirection->y);
}

void Snake::grow() {
    length += GROW_RATE;
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

int Snake::getLength() const {
    return length;
}

unsigned char Snake::getR() const {
    return r;
}

unsigned char Snake::getG() const {
    return g;
}

unsigned char Snake::getB() const {
    return b;
}
