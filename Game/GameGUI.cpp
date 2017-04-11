

#include "GameGUI.hpp"

bool GameGUI::init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow(
                "Snake",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_FULLSCREEN_DESKTOP);

        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    if (not success) printf("Failed to initialize!\n");

    return success;
}

void GameGUI::close() {
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

void GameGUI::update() {
    bool quit = false;
    SDL_Event e;

    while (not quit and not manager->isGameOver()) {
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
                        quit = true;
                        break;

                    default:
                        break;
                }
            }
        }

        SDL_UpdateWindowSurface(gWindow);
    }
}

GameGUI::GameGUI(GameManager *manager) : GameUI(manager) {}
