

#include "Food.hpp"

Food::Food(Position *position) : position(position) {}

const Position *Food::getPosition() const {
    return position;
}
