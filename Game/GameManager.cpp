

#include <iostream>
#include "GameManager.hpp"
#include "GameUI.hpp"
#include "GameCUI.hpp"
#include "GameGUI.hpp"

GameManager::GameManager() : gameOver(false), id(0), stepCount(0) {
    snakes.push_back(new Snake(new Position()));
    snakes.push_back(new Snake(new Position(-50, -5)));
    spawnFood();
    if (isConsole) gameUI = new GameCUI(this);
    else gameUI = new GameGUI(this);
}

void GameManager::run() {
    if (gameUI->init()) {
        srand((unsigned) time(0));
        gameUI->update(id, snakes, food);
    }
    gameUI->close();
}

void GameManager::handleDirection(char directionChar) {
    Position* direction;
    switch (directionChar) {
        case 'U': // UP
            direction = new Position(0, -1);
            break;

        case 'D': // DOWN
            direction = new Position(0, 1);
            break;

        case 'R': // RIGHT
            direction = new Position(1, 0);
            break;

        case 'L': // LEFT
            direction = new Position(-1, 0);
            break;

        default:
            logFile << "Error of direction\n";
            printf("Error of direction\n");
            direction = new Position(0, 0);
            break;
    }
    snakes.at(id)->setTmpDirection(direction);
}

bool GameManager::play() {
    bool killed = false;
    int killer = -1;

    int count = 0;
    for (auto snake : snakes) {
        Position* snakePos = (Position *) snake->getPosition();

        int countOtherSnake = 0;
        for (auto otherSnake : snakes) {
            Position* otherSnakePos = (Position *) otherSnake->getPosition();
            if (*snakePos != *otherSnakePos) {

                Position* nextPos = *snakePos + *snake->getDirection();

                if (*nextPos == *(*otherSnakePos + *otherSnake->getDirection())) killed = true;
                else {

                    int cellCount = 0;
                    for (auto cell : otherSnake->getTail()) {
                        if (nextPos == *cell + *otherSnake->getDirection()) {
                            if (cellCount < INITIAL_LENGTH) {
                                killer = countOtherSnake;
                            } else {
                                killed = true;
                            }
                        }

                        cellCount++;
                    }
                }
            }

            countOtherSnake++;
        }

        if (count == killer) {
            printf(id + "killed" + killer);
            return true;
        }

        if (killed)  {
            gameOver = true;
            std::cout << count << " is dead" << std::endl;
        }
        else gameOver = snake->move();

        bool grow = false;
        Position *cherryPos = new Position();
        for (auto cherry : food) {
            cherryPos = (Position *) cherry->getPosition();
            if (*cherryPos == *snakePos) {
                grow = true;
                break;
            }
        }
        if (grow) {
            snake->grow();
            deleteFood(cherryPos);
        }

        count++;
    }

    if (stepCount > STEP_COUNT_BETWEEN_FOOD_SPAWN) {
        spawnFood();
        stepCount = 0;
    }

    stepCount++;
    return gameOver;
}

void GameManager::spawnFood() {
    int range;
    int tries;

    Position* foodPos;
    int x;
    int y;

    for (auto snake : snakes) {
        range = 40;
        tries = 0;
        do {
            if (tries >= 20) {
                range++;
                tries = 0;
            }
            x = snake->getPosition()->x + rand() % range - range / 2;
            y = snake->getPosition()->y + rand() % range - range / 2;
            foodPos = new Position(x, y);
            tries++;
        } while (snake->onSnake(foodPos));

        food.push_back(new Food(foodPos));
    }
}

void GameManager::deleteFood(Position *foodPos) {
    Position* cherryPos;

    int count = 0;
    for (auto cherry : food) {
        cherryPos = (Position *) cherry->getPosition();
        if (*cherryPos == *foodPos) break;
        count++;
    }

    food.erase(food.begin()+count);
}
