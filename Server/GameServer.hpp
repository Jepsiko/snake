

#ifndef SNAKE_GAMESERVER_HPP
#define SNAKE_GAMESERVER_HPP


#include "Server.hpp"
#include "PlayerConnection.hpp"

class GameServer : public Server {
private:
    std::string mode;
    std::vector<PlayerConnection> playerConnections;

public:

    GameServer(int port, std::vector<PlayerConnection> &playerConnections, std::string _mode);

};


#endif //SNAKE_GAMESERVER_HPP
