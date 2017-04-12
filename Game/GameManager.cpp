

#include "GameManager.hpp"
#include "GameUI.hpp"
#include "GameCUI.hpp"
#include "GameGUI.hpp"

void GameManager::run() {
    if (gameUI->init()) {
        gameUI->update(snake, food);
    }
    gameUI->close();
}

GameManager::GameManager() : snake(new Snake(new Position())), gameOver(false) {
    spawnFood();
    if (isConsole) gameUI = new GameCUI(this);
    else gameUI = new GameGUI(this);
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
    snake->setTmpDirection(direction);
}

bool GameManager::play() {
    // TODO : test if snake->getPosition() + direction != other snake
    logFile << "Play\n";
    if (not gameOver) gameOver = snake->move();

    bool grow = false;
    const Position* snakePos = snake->getPosition();
    Position* cherryPos = new Position();
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
        spawnFood();
    }

    return gameOver;
}

void GameManager::spawnFood() {
    srand((unsigned) time(0));
    int range = 20;
    int tries = 0;

    Position* foodPos;
    int x;
    int y;
    do {
        if (tries >= 20) {
            range++;
            tries = 0;
        }
        x = snake->getPosition()->x + rand()%range - range/2;
        y = snake->getPosition()->y + rand()%range - range/2;
        foodPos = new Position(x, y);
        tries++;
    } while (snake->onSnake(foodPos));

    food.push_back(new Food(foodPos));
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
