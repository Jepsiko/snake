

#ifndef SNAKE_GAMEGUI_HPP
#define SNAKE_GAMEGUI_HPP

#include "../Tools/Constants.hpp"
#include "../Abstract/AbstractGUI.hpp"
#include "GameUI.hpp"

class GameManager;

class GameGUI : public virtual AbstractGUI, public GameUI {
private:
    SDL_Window *gWindow = NULL;
    SDL_Surface *gScreenSurface = NULL;

public:
    GameGUI(GameManager *manager);

    bool init() override;

    void update(const Snake* snake) override;

    void close() override;
};


#endif //SNAKE_GAMEGUI_HPP
