

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
    SDL_Renderer* gRenderer = NULL;
    bool fullscreen;

    void drawTail(const Snake* snake);

    void drawRectOffset(const Position *snakePos, const Position *position, int widthOffset, int heightOffset, Uint8 r,
                        Uint8 g, Uint8 b);

    void drawRect(const Position *position, const Position *position2,
                  Uint8 r, Uint8 g, Uint8 b);

public:
    GameGUI(GameManager *manager);

    bool init() override;

    void update(const Snake* snake, const std::vector<Food*>&) override;

    void close() override;
};


#endif //SNAKE_GAMEGUI_HPP
