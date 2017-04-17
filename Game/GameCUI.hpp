

#ifndef SNAKE_GAMECUI_HPP
#define SNAKE_GAMECUI_HPP

#include "GameUI.hpp"
#include "../Client/Abstract/AbstractCUI.hpp"

class GameManager;

class GameCUI : public virtual AbstractCUI, public GameUI {
private:
    void drawTail(const Snake* snake);

    void drawCell(const Position* snakePos, const Position* position, chtype part, int color_pair);

public:
    GameCUI(GameManager *manager);

    bool init() override;

    void update(unsigned long id, const std::vector<Snake*>& snakes, const std::vector<Food*>& food) override;

    void close() override;
};


#endif //SNAKE_GAMECUI_HPP
