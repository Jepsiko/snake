cmake_minimum_required(VERSION 3.7)
project(Snake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Snake_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)

set(CLIENT_FILES Client/snakeLauncher.cpp
        # ABSTRACT
        Client/Abstract/AbstractManager.hpp
        Client/Abstract/AbstractUI.hpp
        Client/Abstract/AbstractCUI.hpp
        Client/Abstract/AbstractGUI.hpp

        # GAME
        Client/Game/GameManager.cpp
        Client/Game/GameUI.cpp
        Client/Game/GameCUI.cpp
        Client/Game/GameGUI.cpp

        # ENTITIES
        Common/Entities/Snake.cpp
        Common/Entities/Food.cpp

        # TOOLS
        Common/Tools/Constants.hpp
        Common/Tools/Ressources.hpp
        Common/Tools/Global.cpp
        Common/Tools/Timer.cpp

        Common/Position.hpp
        Common/Networking.cpp)

add_executable(Snake ${CLIENT_FILES})
target_link_libraries(Snake ncurses SDL2 SDL2_image)

set(SERVER_FILES Server/serverLauncher.cpp

        Server/Server.cpp

        # ENTITIES
        Common/Entities/Snake.cpp
        Common/Entities/Food.cpp

        # TOOLS
        Common/Tools/Constants.hpp
        Common/Tools/Ressources.hpp
        Common/Tools/Global.cpp
        Common/Tools/Timer.cpp

        Common/Position.hpp
        Common/Networking.cpp Server/GameServer.cpp Server/GameServer.hpp Server/PlayerConnection.cpp Server/PlayerConnection.hpp Server/GameEngine.cpp Server/GameEngine.hpp)

add_executable(SnakeServer ${SERVER_FILES})