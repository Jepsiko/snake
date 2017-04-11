

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
    SDL_Event e; //TODO : put that into the GameGUI class

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        printf("up");
                        break;
                    case SDLK_DOWN:
                        printf("down");
                        break;
                    case SDLK_RIGHT:
                        printf("right");
                        break;
                    case SDLK_LEFT:
                        printf("left");
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        printf("other");
                        break;
                }
                printf("\n");
            }
        }

        SDL_UpdateWindowSurface(gWindow);
    }
}

GameGUI::GameGUI(GameManager *manager) : GameUI(manager) {}
