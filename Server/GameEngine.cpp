

#include "GameEngine.hpp"

void GameEngine::run() {
    /*
    if (gameUI->init()) {
        srand((unsigned) time(0));
        gameUI->update(id, snakes, food);
    }
    gameUI->close();
    */
}

void GameEngine::handleDirection(char directionChar) {
    Position *direction;
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

bool GameEngine::play() {

    // Computes all the killed snakes id
    std::vector<unsigned long> killedSnakesId;
    unsigned long count = 0;
    for (auto snake : snakes) {
        Position *snakePos = (Position *) snake->getPosition();
        Position *nextPos = *snakePos + *snake->getDirection();

        unsigned long countOtherSnake = 0;
        for (auto otherSnake : snakes) {
            Position *otherSnakePos = (Position *) otherSnake->getPosition();
            Position *nextOtherPos = *otherSnakePos + *otherSnake->getDirection();

            if (count != countOtherSnake) {
                if (*nextPos == *otherSnakePos or *nextPos == *nextOtherPos) {
                    killedSnakesId.push_back(count);
                } else {

                    int cellCount = 0;
                    for (auto cell : otherSnake->getTail()) {
                        if (*nextPos == *cell) {
                            if (cellCount < INITIAL_LENGTH) {
                                killedSnakesId.push_back(countOtherSnake);
                            }
                            if (cellCount >= INITIAL_LENGTH) {
                                killedSnakesId.push_back(count);
                            }
                        }

                        cellCount++;
                    }
                }
            }

            countOtherSnake++;
        }

        count++;
    }

    for (unsigned long i = killedSnakesId.size(); i-- > 0;) {
        Snake *snake = snakes.at(killedSnakesId.at(i));

        for (auto cell : snake->getTail()) {
            food.push_back(new Food(cell));
        }

        snakes.erase(snakes.begin() + killedSnakesId.at(i));
    }

    // Moves all the snakes and makes them grow if they eat
    for (auto snake : snakes) {
        snake->move();

        bool grow = false;
        Position *cherryPos = new Position();
        for (auto cherry : food) {
            cherryPos = (Position *) cherry->getPosition();
            if (*cherryPos == *snake->getPosition()) {
                grow = true;
                break;
            }
        }
        if (grow) {
            snake->grow();
            deleteFood(cherryPos);
        }
    }

    // Spawns the food
    if (stepCount % STEP_COUNT_BETWEEN_FOOD_SPAWN == 0) spawnFood();
    if (stepCount % 120 == 0) snakes.push_back(new Snake(new Position(-50, 0)));
    stepCount++;

    // TODO : Send the gameState to all players

    return snakes.size() == 0;
}

void GameEngine::spawnFood() {
    int range;
    int tries;

    Position *foodPos;
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

void GameEngine::deleteFood(Position *foodPos) {
    Position *cherryPos;

    int count = 0;
    for (auto cherry : food) {
        cherryPos = (Position *) cherry->getPosition();
        if (*cherryPos == *foodPos) break;
        count++;
    }

    food.erase(food.begin() + count);
}