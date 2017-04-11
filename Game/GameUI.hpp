

#ifndef SNAKE_GAMEUI_HPP
#define SNAKE_GAMEUI_HPP

#include "ncurses.h"
#include "../Abstract/AbstractUI.hpp"

class GameUI : public AbstractUI {

public:
    bool init() override;

    void update() override;

    void close() override;
};


#endif //SNAKE_GAMEUI_HPP
