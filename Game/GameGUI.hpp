

#ifndef SNAKE_GAMEGUI_HPP
#define SNAKE_GAMEGUI_HPP

#include "../Tools/Constants.hpp"
#include "../Abstract/AbstractGUI.hpp"

class GameGUI : public AbstractGUI {
private:
    SDL_Window *gWindow = NULL;
    SDL_Surface *gScreenSurface = NULL;

public:
    GameGUI();

    bool init() override;

    void update() override;

    void close() override;
};


#endif //SNAKE_GAMEGUI_HPP
