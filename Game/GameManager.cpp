

#include "GameManager.hpp"
#include "GameUI.hpp"
#include "GameCUI.hpp"
#include "GameGUI.hpp"

void GameManager::run() {
    if (gameUI->init()) {
        gameUI->update(snake);
    }
    gameUI->close();
}

GameManager::GameManager() : snake(new Snake()), gameOver(false) {
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
            printf("Error of direction");
            direction = new Position(0, 0);
            break;
    }
    snake->setDirection(direction);
}

bool GameManager::play() {
    // TODO : test if snake->getPosition() + direction != obstacle (or other snake if multiplayer ?)
    if (not gameOver) gameOver = snake->move();
    return gameOver;
}
