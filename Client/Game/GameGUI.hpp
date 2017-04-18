

#ifndef SNAKE_GAMEGUI_HPP
#define SNAKE_GAMEGUI_HPP

#include "../../Common/Tools/Constants.hpp"
#include "../Abstract/AbstractGUI.hpp"
#include "GameUI.hpp"

class GameManager;

class GameGUI : public virtual AbstractGUI, public GameUI {
private:
    SDL_Window *gWindow = NULL;
    SDL_Surface *gScreenSurface = NULL;
    SDL_Renderer* gRenderer = NULL;
    bool fullscreen;

    void drawTail(const Position *mySnakePos, const Snake* snake);

    void drawRectOffset(const Position *mySnakePos, const Position *position,
                        int widthOffset, int heightOffset, Uint8 color[3]);

    void drawRect(const Position *position, const Position *position2, Uint8 color[3]);

public:
    GameGUI(GameManager *manager);

    bool init() override;

    void update(unsigned long id, const std::vector<Snake*>& snakes, const std::vector<Food*>&) override;

    void close() override;
};


#endif //SNAKE_GAMEGUI_HPP
