
#include <string>
#include "GameCUI.hpp"
#include "../Tools/Constants.hpp"

// Directions
const Position* UP = new Position(0, -1);
const Position* DOWN = new Position(0, 1);
const Position* RIGHT = new Position(1, 0);
const Position* LEFT = new Position(-1, 0);

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
            Position* after = (Position *) snake->getPosition();
            Position* before;
            Position* pos;
            for (unsigned long i = snake->getTail().size(); i-- > 0; ) {
                pos = snake->getTail().at(i);
                before = snake->getTail().size() > i-1 ? snake->getTail().at(i-1) : NULL;

                if (before == NULL) {
                    mvaddch(height/2 + pos->y - snake->getPosition()->y,
                            width/2 + pos->x - snake->getPosition()->x,
                            '*');
                } else {
                    Position* nextDirection = *after - *pos;
                    Position* postDirection = *before - *pos;

                    logFile << pos->to_string() << " ";
                    logFile << after->to_string() << " ";;
                    logFile << nextDirection->to_string() << " ";
                    logFile << before->to_string() << " ";
                    logFile << postDirection->to_string() << "\n";

                    if ((*nextDirection == *UP and *postDirection == *DOWN) or
                            (*nextDirection == *DOWN and *postDirection == *UP)) {
                        mvaddch(height/2 + pos->y - snake->getPosition()->y,
                                width/2 + pos->x - snake->getPosition()->x,
                                ACS_VLINE);
                    } else if ((*nextDirection == *LEFT and *postDirection == *RIGHT) or
                              (*nextDirection == *RIGHT and *postDirection == *LEFT)) {
                        mvaddch(height/2 + pos->y - snake->getPosition()->y,
                                width/2 + pos->x - snake->getPosition()->x,
                                ACS_HLINE);
                    } else if ((*nextDirection == *LEFT and *postDirection == *UP) or
                               (*nextDirection == *UP and *postDirection == *LEFT)) {
                        mvaddch(height/2 + pos->y - snake->getPosition()->y,
                                width/2 + pos->x - snake->getPosition()->x,
                                ACS_LRCORNER);
                    } else if ((*nextDirection == *LEFT and *postDirection == *DOWN) or
                              (*nextDirection == *DOWN and *postDirection == *LEFT)) {
                        mvaddch(height/2 + pos->y - snake->getPosition()->y,
                                width/2 + pos->x - snake->getPosition()->x,
                                ACS_URCORNER);
                    } else if ((*nextDirection == *RIGHT and *postDirection == *UP) or
                               (*nextDirection == *UP and *postDirection == *RIGHT)) {
                        mvaddch(height/2 + pos->y - snake->getPosition()->y,
                                width/2 + pos->x - snake->getPosition()->x,
                                ACS_LLCORNER);
                    } else if ((*nextDirection == *RIGHT and *postDirection == *DOWN) or
                               (*nextDirection == *DOWN and *postDirection == *RIGHT)) {
                        mvaddch(height/2 + pos->y - snake->getPosition()->y,
                                width/2 + pos->x - snake->getPosition()->x,
                                ACS_ULCORNER);
                    } else {
                        mvaddch(height/2 + pos->y - snake->getPosition()->y,
                                width/2 + pos->x - snake->getPosition()->x,
                                'x');
                    }
                }

                after = pos;
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
