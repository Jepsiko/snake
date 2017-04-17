
#include <string>
#include "GameCUI.hpp"
#include "../Common/Tools/Constants.hpp"

bool GameCUI::init() {
    try {
        initscr();
        noecho();
        cbreak();
        scrollok(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);
        start_color();

        timer->reset();
        return true;
    } catch (...) {
        logFile << "Failed to initialize!\n";
        printf("Failed to initialize!\n");
        return false;
    };
}

void GameCUI::update(unsigned long id, const std::vector<Snake*>& snakes, const std::vector<Food*>& food) {
    bool quit = false;
    unsigned char color[3];

    while(not quit) {
        // Play every TIME_BETWEEN_STEPS milliseconds
        if (timer->elapsedTimeInMiliseconds() >= TIME_BETWEEN_STEPS) {
            height = LINES;
            width = COLS;

            clear();

            if (not manager->play()) timer->reset();
            else quit = true;

            Snake* mySnake = snakes.at(id);

            for (auto snake : snakes) {
                // Draw the snake's tail
                drawTail(snake);

                // Draw the snake's head
                color[0] = snake->getR();
                color[1] = snake->getG();
                color[2] = snake->getB();
                init_color(COLOR_GREEN,
                           (short) (color[0] * 1000 / 256),
                           (short) (color[1] * 1000 / 256),
                           (short) (color[2] * 1000 / 256));
                init_pair(1, COLOR_GREEN, COLOR_BLACK);
                drawCell(mySnake->getPosition(), snake->getPosition(), '#', 1);

                // Draw the food
                color[0] = 0xFF;
                color[1] = 0x00;
                color[2] = 0x00;
                init_color(COLOR_RED,
                           (short) (color[0] * 1000 / 256),
                           (short) (color[1] * 1000 / 256),
                           (short) (color[2] * 1000 / 256));
                init_pair(2, COLOR_RED, COLOR_BLACK);
                for (auto cherry : food) {
                    drawCell(mySnake->getPosition(), cherry->getPosition(), 'O', 2);
                }
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

    unsigned char color[3];
    int color_pair;

    color[0] = (unsigned char) (snake->getR() + 0x60);
    color[1] = (unsigned char) (snake->getG() + 0x6F);
    color[2] = snake->getB();
    init_color(COLOR_BLUE,
               (short) (color[0] * 1000 / 256),
               (short) (color[1] * 1000 / 256),
               (short) (color[2] * 1000 / 256));
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    color[0] = snake->getR();
    color[1] = (unsigned char) (snake->getG() + 0x6F);
    color[2] = snake->getB();
    init_color(COLOR_CYAN,
               (short) (color[0] * 1000 / 256),
               (short) (color[1] * 1000 / 256),
               (short) (color[2] * 1000 / 256));
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    Position* after;
    Position* before;
    Position* pos;
    chtype part = '?';

    for (unsigned long i = 0; i < snake->getTail().size(); i++) {

        pos = snake->getTail().at(i);
        after = snake->getTail().size() > i-1 ? snake->getTail().at(i-1) : NULL;
        before = snake->getTail().size() > i+1 ? snake->getTail().at(i+1) : (Position*) snake->getPosition();

        if (i < INITIAL_LENGTH) {
            color_pair = 3;
            part = 'o';
        } else {
            color_pair = 4;
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

        drawCell(snake->getPosition(), pos, part, color_pair);
    }
}

void GameCUI::drawCell(const Position* snakePos, const Position *position, chtype part, int color_pair) {
    attron(COLOR_PAIR(color_pair));
    mvaddch(height/2 + position->y - snakePos->y,
            width/2 + position->x - snakePos->x,
            part);
    attroff(COLOR_PAIR(color_pair));
}
