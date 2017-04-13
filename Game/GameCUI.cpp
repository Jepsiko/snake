
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
            drawCell(snake->getPosition(), snake->getPosition(), '#');

            // Draw the snake's tail
            drawTail(snake);

            // Draw the food
            for (auto cherry : food) {
                drawCell(snake->getPosition(), cherry->getPosition(), 'O');
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

void GameCUI::drawTail(const Snake* snake) {
    // Directions
    const Position* UP = new Position(0, -1);
    const Position* DOWN = new Position(0, 1);
    const Position* RIGHT = new Position(1, 0);
    const Position* LEFT = new Position(-1, 0);

    Position* after = (Position *) snake->getPosition();
    Position* before;
    Position* pos;
    chtype part = '?';

    for (unsigned long i = snake->getTail().size(); i-- > 0; ) {
        pos = snake->getTail().at(i);
        before = snake->getTail().size() > i-1 ? snake->getTail().at(i-1) : NULL;

        if (before == NULL) {
            part = '*';
        } else {
            Position* nextDirection = *after - *pos;
            Position* postDirection = *before - *pos;

            if ((*nextDirection == *UP and *postDirection == *DOWN) or
                (*nextDirection == *DOWN and *postDirection == *UP)) {
                part = ACS_VLINE;
            }
            else if ((*nextDirection == *LEFT and *postDirection == *RIGHT) or
                       (*nextDirection == *RIGHT and *postDirection == *LEFT)) {
                part = ACS_HLINE;
            }
            else if ((*nextDirection == *LEFT and *postDirection == *UP) or
                       (*nextDirection == *UP and *postDirection == *LEFT)) {
                part = ACS_LRCORNER;
            }
            else if ((*nextDirection == *LEFT and *postDirection == *DOWN) or
                       (*nextDirection == *DOWN and *postDirection == *LEFT)) {
                part = ACS_URCORNER;
            }
            else if ((*nextDirection == *RIGHT and *postDirection == *UP) or
                       (*nextDirection == *UP and *postDirection == *RIGHT)) {
                part = ACS_LLCORNER;
            }
            else if ((*nextDirection == *RIGHT and *postDirection == *DOWN) or
                       (*nextDirection == *DOWN and *postDirection == *RIGHT)) {
                part = ACS_ULCORNER;
            }
        }

        drawCell(snake->getPosition(), pos, part);
        after = pos;
    }
}

void GameCUI::drawCell(const Position* snakePos, const Position *position, chtype part) {
    mvaddch(height/2 + position->y - snakePos->y,
            width/2 + position->x - snakePos->x,
            part);
}
