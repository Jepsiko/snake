

#ifndef SNAKE_FOOD_HPP
#define SNAKE_FOOD_HPP


#include "../Position.hpp"

class Food {
private:
    Position* position;

public:
    Food(Position* position);

    const Position* getPosition() const;
};


#endif //SNAKE_FOOD_HPP
