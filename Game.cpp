

#include "Game.hpp"

void Game::run() {
    gameGUI = new GameGUI();

    if (!gameGUI->init()) {
        printf("Failed to initialize!\n");
    } else {
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
                        default:
                            printf("other");
                            break;
                    }
                    printf("\n");
                }
            }

            gameGUI->update();
        }
    }

    gameGUI->close();
}

Game::Game() : gameGUI(NULL) {

}
