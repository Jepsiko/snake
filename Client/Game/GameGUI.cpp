

#include "GameGUI.hpp"

bool GameGUI::init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logFile << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        success = false;
    } else {
        gWindow = SDL_CreateWindow(
                "Snake",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                640,
                480,
                SDL_WINDOW_RESIZABLE);
        SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
        fullscreen = true;

        if (gWindow == NULL) {
            logFile << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL) {
                logFile << "Renderer could not be created! SDL Error: %s\n", SDL_GetError();
                success = false;
            } else {
                timer->reset();
                gScreenSurface = SDL_GetWindowSurface(gWindow);
                SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));
                offset = tileSize/10*2;
            }
        }
    }

    if (not success) logFile << "Failed to initialize!\n";

    return success;
}

void GameGUI::update(unsigned long id, const std::vector<Snake*>& snakes, const std::vector<Food*>& food) {
    bool quit = false;
    SDL_Event e;
    int* tmpWidth = new int(0);
    int* tmpHeight = new int(0);

    while (not quit) {

        // Play every TIME_BETWEEN_STEPS milliseconds
        if (timer->elapsedTimeInMiliseconds() >= TIME_BETWEEN_STEPS) {
            if (not manager->play()) timer->reset();
            else return;

            SDL_GetWindowSize(gWindow, tmpWidth, tmpHeight);
            width = *tmpWidth;
            height = *tmpHeight;

            // Clear
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);


            Uint8 color[3];

            Snake* mySnake = snakes.at(id);

            for (auto snake : snakes) {
                // Draw the snake's tail
                drawTail(mySnake->getPosition(), snake);

                // Draw the snake's head
                color[0] = snake->getR();
                color[1] = snake->getG();
                color[2] = snake->getB();
                drawRectOffset(mySnake->getPosition(), snake->getPosition(), 0, 0, color);

                // Draw the food
                color[0] = 0xFF;
                color[1] = 0x00;
                color[2] = 0x00;
                for (auto cherry : food) {
                    drawRectOffset(mySnake->getPosition(), cherry->getPosition(), offset*3, offset*3, color);
                }
            }

            SDL_RenderPresent(gRenderer);
        }

        // Event handler
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEWHEEL:
                    if (e.wheel.y < 0 and tileSize >= 20)
                        tileSize -= 2;
                    else if (tileSize <= 40)
                        tileSize += 2;
                    offset = tileSize/10*2;
                    break;

                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                        case SDLK_z: // 'Z' Key Code : UP
                            manager->handleDirection('U');
                            break;

                        case SDLK_s: // 'S' Key Code : DOWN
                            manager->handleDirection('D');
                            break;

                        case SDLK_d: // 'D' Key Code : RIGHT
                            manager->handleDirection('R');
                            break;

                        case SDLK_q: // 'Q' Key Code : LEFT
                            manager->handleDirection('L');
                            break;

                        case SDLK_ESCAPE:
                            if (fullscreen) {
                                SDL_SetWindowFullscreen(gWindow, 0);
                                fullscreen = false;
                            } else {
                                SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
                                fullscreen = true;
                            }
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

void GameGUI::close() {
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

GameGUI::GameGUI(GameManager *manager) : GameUI(manager) {}

void GameGUI::drawTail(const Position* mySnakePos, const Snake* snake) {
    // Directions
    const Position* UP = new Position(0, -1);
    const Position* DOWN = new Position(0, 1);
    const Position* RIGHT = new Position(1, 0);
    const Position* LEFT = new Position(-1, 0);

    Uint8 color[3];

    Position* after;
    Position* before;
    Position* pos;

    for (unsigned long i = 0; i < snake->getTail().size(); i++) {

        int xOffset = 0;
        int yOffset = 0;

        pos = snake->getTail().at(i);
        after = snake->getTail().size() > i-1 ? snake->getTail().at(i-1) : NULL;
        before = snake->getTail().size() > i+1 ? snake->getTail().at(i+1) : (Position*) snake->getPosition();

        if (i < INITIAL_LENGTH) {
            color[0] = (Uint8) (snake->getR() + 0x60);
            color[1] = (Uint8) (snake->getG() + 0x6F);
            color[2] = snake->getB();

            xOffset = (int) ((INITIAL_LENGTH - i+1)/2*offset/2+2);
            yOffset = (int) ((INITIAL_LENGTH - i+1)/2*offset/2+2);
        } else {
            color[0] = snake->getR();
            color[1] = (Uint8) (snake->getG() + 0x6F);
            color[2] = snake->getB();

            Position* nextDirection = *after - *pos;
            Position* postDirection = *before - *pos;

            if ((*nextDirection == *UP and *postDirection == *DOWN) or
                (*nextDirection == *DOWN and *postDirection == *UP)) {
                xOffset = offset;
            }
            else if ((*nextDirection == *LEFT and *postDirection == *RIGHT) or
                     (*nextDirection == *RIGHT and *postDirection == *LEFT)) {
                yOffset = offset;
            } else {
                xOffset = offset;
                yOffset = offset;
                Position* pos1 = new Position();
                Position* pos2 = new Position();

                int x1 = width/2 + (pos->x - snake->getPosition()->x)*tileSize;
                int y1 = height/2 + (pos->y - snake->getPosition()->y)*tileSize;
                int x2 = width/2 + (pos->x+1 - snake->getPosition()->x)*tileSize;
                int y2 = height/2 + (pos->y+1 - snake->getPosition()->y)*tileSize;

                if (*nextDirection == *LEFT or *postDirection == *LEFT) {
                    pos1->x = x1;
                    pos1->y = y1 + yOffset/2;

                    pos2->x = x2 - xOffset/2;
                    pos2->y = y2 - yOffset/2;
                    drawRect(pos1, pos2, color);
                }
                if (*nextDirection == *UP or *postDirection == *UP) {
                    pos1->x = x1 + xOffset/2;
                    pos1->y = y1;

                    pos2->x = x2 - xOffset/2;
                    pos2->y = y2 - yOffset/2;
                    drawRect(pos1, pos2, color);
                }
                if (*nextDirection == *RIGHT or *postDirection == *RIGHT) {
                    pos1->x = x2 - xOffset/2;
                    pos1->y = y1 + yOffset/2;

                    pos2->x = x2;
                    pos2->y = y2 - yOffset/2;
                    drawRect(pos1, pos2, color);
                }
                if (*nextDirection == *DOWN or *postDirection == *DOWN) {
                    pos1->x = x1 + xOffset/2;
                    pos1->y = y2 - yOffset/2;

                    pos2->x = x2 - xOffset/2;
                    pos2->y = y2;
                    drawRect(pos1, pos2, color);
                }
            }
        }

        drawRectOffset(mySnakePos, pos, xOffset, yOffset, color);
    }
}

void GameGUI::drawRectOffset(const Position *mySnakePos, const Position *position,
                             int widthOffset, int heightOffset, Uint8 color[3]) {
    SDL_Rect fillRect;
    fillRect = {width/2 + (position->x - mySnakePos->x)*tileSize + widthOffset/2,
                height/2 + (position->y - mySnakePos->y)*tileSize + heightOffset/2,
                tileSize - widthOffset, tileSize - heightOffset};
    SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);
}

void GameGUI::drawRect(const Position *position1, const Position *position2, Uint8 color[3]) {
    SDL_Rect fillRect;
    fillRect = {position1->x,
                position1->y,
                position2->x - position1->x,
                position2->y - position1->y};
    SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);
}