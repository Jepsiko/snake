

#ifndef SNAKE_GAMEGUI_HPP
#define SNAKE_GAMEGUI_HPP

#include <SDL2/SDL.h>
#include "Constants.hpp"

class GameGUI {
private:
    SDL_Window *gWindow = NULL;
    SDL_Surface *gScreenSurface = NULL;

public:
    GameGUI();

    bool init();

    void update();

    void close();
};


#endif //SNAKE_GAMEGUI_HPP
