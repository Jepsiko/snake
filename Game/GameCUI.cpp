

#include "GameCUI.hpp"

bool GameCUI::init() {
    try {
        initscr();
        return true;
    } catch (...) {
        printf("Failed to initialize!\n");
        return false;
    };
}

void GameCUI::update() {
    printw("Hello World");
    refresh();
    getch();
}

void GameCUI::close() {
    endwin();
}

GameCUI::GameCUI(GameManager *manager) : GameUI(manager) {}
