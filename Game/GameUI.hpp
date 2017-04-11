

#ifndef SNAKE_GAMEUI_HPP
#define SNAKE_GAMEUI_HPP


#include "../Abstract/AbstractUI.hpp"
#include "GameManager.hpp"

class GameUI : public virtual AbstractUI {
protected:
    GameManager* manager;

public:
    GameUI(GameManager *manager);
};


#endif //SNAKE_GAMEUI_HPP
