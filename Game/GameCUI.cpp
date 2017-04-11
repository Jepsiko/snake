
#include <string>
#include "GameCUI.hpp"
#include <ctime>

bool GameCUI::init() {
    try {
        initscr();
        noecho();
        cbreak();
        timer->start();
        return true;
    } catch (...) {
        printf("Failed to initialize!\n");
        return false;
    };
}

void GameCUI::update(const Snake* snake) {
    bool quit = false;

    while(not quit) {
        clear();

        if (timer->elapsedTimeInSeconds() >= 1) {
            if (manager->play()) timer->reset();
            else quit = true;
        }

        mvaddch(snake->getPosition()->y, snake->getPosition()->x, 'H');

        for (auto pos : snake->getTail()) {
            mvaddch(pos->y, pos->x, '.');
        }

        refresh();
        int key = getch();
        switch (key) {
            case 27: // Escape Key Code
                quit = true;
                break;

            case 122: // 'Z' Key Code : UP
                manager->handleDirection('U');
                break;

            case 115: // 'S' Key Code : DOWN
                manager->handleDirection('D');
                break;

            case 113: // 'Q' Key Code : LEFT
                manager->handleDirection('L');
                break;

            case 100: // 'D' Key Code : RIGHT
                manager->handleDirection('R');
                break;

            default:
                break;
        }
    }
}

void GameCUI::close() {
    endwin();
}

GameCUI::GameCUI(GameManager *manager) : GameUI(manager) {}
