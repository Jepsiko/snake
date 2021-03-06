

#ifndef SNAKE_PLAYERCONNECTION_HPP
#define SNAKE_PLAYERCONNECTION_HPP

#include <string>


class PlayerConnection {

private:
    int player_id;
    int socket_fd;
    std::string username;

public:

    PlayerConnection() = default;

    std::string &getUsername();

    PlayerConnection(int id, int socket);

    int getPlayer_id();

    int getSocketFd();

    void setPlayer_id(int player_id);

    void setSocket_fd(int socket_fd);

    ~PlayerConnection();

    bool operator==(const PlayerConnection &rhs) const;

    bool operator!=(const PlayerConnection &rhs) const;

    void setUsername(const std::string &username);
};


#endif //SNAKE_PLAYERCONNECTION_HPP
