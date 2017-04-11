

#ifndef SNAKE_GAMECUI_HPP
#define SNAKE_GAMECUI_HPP

#include "GameUI.hpp"
#include "../Abstract/AbstractCUI.hpp"

class GameManager;

class GameCUI : public virtual AbstractCUI, public GameUI {

public:
    GameCUI(GameManager *manager);

    bool init() override;

    void update() override;

    void close() override;
};


#endif //SNAKE_GAMECUI_HPP
