
#include <string>
#include "GameCUI.hpp"
#include "../Tools/Constants.hpp"

bool GameCUI::init() {
    try {
        initscr();
        noecho();
        cbreak();
        scrollok(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);

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
        height = LINES;
        width = COLS;
        clear();

        if (timer->elapsedTimeInMiliseconds() >= TIME_BETWEEN_STEPS) {
            if (not manager->play()) timer->reset();
            else quit = true;
        }

        mvaddch(height/2,
                width/2,
                '#');

        for (auto pos : snake->getTail()) {
            mvaddch(height/2+pos->y-snake->getPosition()->y,
                    width/2+pos->x-snake->getPosition()->x,
                    '*');
        }

        for (auto cherry : food) {
            mvaddch(height/2+cherry->getPosition()->y-snake->getPosition()->y,
                    width/2+cherry->getPosition()->x-snake->getPosition()->x,
                    'O');
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
