
#include "Global.hpp"
#include <ctime>

std::string filename() {
    std::string file = "log/log_";

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y_%H:%M:%S",timeinfo);
    std::string str(buffer);

    file += str;
    file += ".txt";

    return file;
}

bool isConsole;

std::ofstream logFile(filename(), std::ios_base::app);

int height;
int width;
