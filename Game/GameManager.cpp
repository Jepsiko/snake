

#include "GameManager.hpp"

#include "GameUI.hpp"
#include "GameCUI.hpp"
#include "GameGUI.hpp"

void GameManager::run() {
    if (gameUI->init()) {
        gameUI->update();
    }

    gameUI->close();
}

GameManager::GameManager() {
    if (isConsole) gameUI = new GameCUI(this);
    else gameUI = new GameGUI(this);
}
