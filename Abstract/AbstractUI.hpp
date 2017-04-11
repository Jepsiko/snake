

#ifndef SNAKE_ABSTRACTUI_HPP
#define SNAKE_ABSTRACTUI_HPP


class AbstractUI {
public:
    virtual bool init() = 0;

    virtual void update() = 0;

    virtual void close() = 0;
};


#endif //SNAKE_ABSTRACTUI_HPP
