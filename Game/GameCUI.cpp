
#include <string>
#include "GameCUI.hpp"

bool GameCUI::init() {
    try {
        initscr();
        noecho();
        cbreak();
        scrollok(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);

        height = LINES;
        width = COLS;

        timer->reset();
        return true;
    } catch (...) {
        logFile << "Failed to initialize!\n";
        printf("Failed to initialize!\n");
        return false;
    };
}

void GameCUI::update(const Snake* snake, const std::vector<Food*>& food) {
    bool quit = false;

    while(not quit) {
        clear();

        if (timer->elapsedTimeInMiliseconds() >= 300) {
            if (not manager->play()) timer->reset();
            else quit = true;
        }

        mvaddch(snake->getPosition()->y, snake->getPosition()->x, '#');

        for (auto pos : snake->getTail()) {
            mvaddch(pos->y, pos->x, '*');
        }

        for (auto cherry : food) {
            mvaddch(cherry->getPosition()->y, cherry->getPosition()->x, 'O');
        }

        refresh();
        int key = getch();
        switch (key) {
            case 27: // Escape Key Code
                quit = true;
                break;

            case 'z':
            case 'Z': // UP
                manager->handleDirection('U');
                break;

            case 's':
            case 'S': // DOWN
                manager->handleDirection('D');
                break;

            case 'q':
            case 'Q': // LEFT
                manager->handleDirection('L');
                break;

            case 'd':
            case 'D': // RIGHT
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
