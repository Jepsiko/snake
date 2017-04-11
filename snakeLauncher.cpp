#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game/GameManager.hpp"
#include "Tools/Ressources.hpp"
#include "Game/GameUI.hpp"


bool init();

bool loadMedia();

void close();

SDL_Surface *loadSurface(const char *path);


SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gSnakeLauncher = NULL;

int main(int argc, char **argv) {

    //Initialize SDL
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            SDL_BlitSurface(gSnakeLauncher, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);

            SDL_Delay(1000);
        }
    }

    close();

    Game game = Game();
    game.run();

    return 0;
}

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow(
                "Snake Launcher",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_BORDERLESS);

        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            int imgFlags = IMG_INIT_PNG;
            if (!IMG_Init(imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            } else {
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    gSnakeLauncher = loadSurface(snakeLauncherFilename);
    if (gSnakeLauncher == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n",
               snakeLauncherFilename, SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    SDL_FreeSurface(gSnakeLauncher);
    gSnakeLauncher = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Surface *loadSurface(const char *path) {
    //The final optimized image
    SDL_Surface *optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return NULL;
    } else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
        return optimizedSurface;
    }
}