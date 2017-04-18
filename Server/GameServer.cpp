

#include "GameServer.hpp"

GameServer::GameServer(int port, std::vector<PlayerConnection> &playerConnections, std::string _mode) :
        Server(port), playerConnections(playerConnections), mode(_mode) {}