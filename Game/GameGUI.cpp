

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
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
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
            }
        }
    }

    if (not success) logFile << "Failed to initialize!\n";

    return success;
}

void GameGUI::update(const Snake* snake, const std::vector<Food*>& food) {
    bool quit = false;
    SDL_Event e;
    int* tmpWidth = new int(0);
    int* tmpHeight = new int(0);
    SDL_Rect fillRect;

    while (not quit) {

        // Play every TIME_BETWEEN_STEPS milliseconds
        if (timer->elapsedTimeInMiliseconds() >= TIME_BETWEEN_STEPS) {
            if (not manager->play()) timer->reset();
            else quit = true;

            SDL_GetWindowSize(gWindow, tmpWidth, tmpHeight);
            width = *tmpWidth;
            height = *tmpHeight;

            // Clear
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            // Draw the snake's head
            fillRect = {width/2,
                        height/2,
                        IMAGE_SIZE_PIXELS, IMAGE_SIZE_PIXELS};
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF); // GREEN
            SDL_RenderFillRect(gRenderer, &fillRect);

            // Draw the snake's tail
            for (auto pos : snake->getTail()) {
                fillRect = {width/2 + (pos->x - snake->getPosition()->x)*IMAGE_SIZE_PIXELS,
                            height/2 + (pos->y - snake->getPosition()->y)*IMAGE_SIZE_PIXELS,
                            IMAGE_SIZE_PIXELS, IMAGE_SIZE_PIXELS};
                SDL_SetRenderDrawColor(gRenderer, 0x9F, 0xFF, 0x9F, 0xFF); // DARK GREEN
                SDL_RenderFillRect(gRenderer, &fillRect);
            }

            // Draw the food
            for (auto cherry : food) {
                fillRect = {width/2 + (cherry->getPosition()->x - snake->getPosition()->x)*IMAGE_SIZE_PIXELS,
                            height/2 + (cherry->getPosition()->y - snake->getPosition()->y)*IMAGE_SIZE_PIXELS,
                            IMAGE_SIZE_PIXELS, IMAGE_SIZE_PIXELS};
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF); // RED
                SDL_RenderFillRect(gRenderer, &fillRect);
            }

            SDL_RenderPresent(gRenderer);
        }

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
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
