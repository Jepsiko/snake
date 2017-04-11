

#ifndef SNAKE_GAMEUI_HPP
#define SNAKE_GAMEUI_HPP


#include "../Abstract/AbstractUI.hpp"
#include "GameManager.hpp"
#include "../Tools/Timer.hpp"

class GameUI : public virtual AbstractUI {
protected:
    GameManager* manager;
    Timer* timer;

public:
    GameUI(GameManager *manager);
};


#endif //SNAKE_GAMEUI_HPP
