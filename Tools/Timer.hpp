

#ifndef SNAKE_TIMER_HPP
#define SNAKE_TIMER_HPP


#include "sys/time.h"

class Timer {
private:
    struct timeval last_pause_timeval;
    int numOfElapsedMilisecondsInPreviousIntervals;
    bool isPaused;

    int getMilisecondsSinceLastCurrentIntervalStart();

public:
    Timer();

    void start();
    void reset();

    int elapsedTimeInSeconds();
    int elapsedTimeInMiliseconds();
};


#endif //SNAKE_TIMER_HPP
