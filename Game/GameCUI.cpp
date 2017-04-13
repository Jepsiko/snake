
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
        // Play every TIME_BETWEEN_STEPS milliseconds
        if (timer->elapsedTimeInMiliseconds() >= TIME_BETWEEN_STEPS) {
            height = LINES;
            width = COLS;

            clear();

            if (not manager->play()) timer->reset();
            else quit = true;

            // Draw the snake's head
            mvaddch(height/2,
                    width/2,
                    '#');

            // Draw the snake's tail
            unsigned long count = snake->getTail().size();
            Position* before = (Position *) snake->getPosition();
            Position* after;
            for (auto pos : snake->getTail()) {
                after = snake->getTail().size() > count ? snake->getTail().at(count) : NULL;

                if (after == NULL) {
                    mvaddch(height/2 + pos->y - snake->getPosition()->y,
                            width/2 + pos->x - snake->getPosition()->x,
                            '*');
                } else {
                    mvaddch(height/2 + pos->y - snake->getPosition()->y,
                            width/2 + pos->x - snake->getPosition()->x,
                            ACS_HLINE);
                }

                before = pos;
                count--;
            }

            // Draw the food
            for (auto cherry : food) {
                mvaddch(height/2 + cherry->getPosition()->y - snake->getPosition()->y,
                        width/2 + cherry->getPosition()->x - snake->getPosition()->x,
                        'O');
            }

            refresh();
        }

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
