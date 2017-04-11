

#ifndef SNAKE_ABSTRACTUI_HPP
#define SNAKE_ABSTRACTUI_HPP


#include "AbstractManager.hpp"

class AbstractUI {
public:
    virtual ~AbstractUI() = default;

    virtual bool init() = 0;

    virtual void update() = 0;

    virtual void close() = 0;
};


#endif //SNAKE_ABSTRACTUI_HPP
