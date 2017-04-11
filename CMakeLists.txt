cmake_minimum_required(VERSION 3.7)
project(Snake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Snake_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES snakeLauncher.cpp

        # ABSTRACT
        Abstract/AbstractManager.cpp
        Abstract/AbstractUI.cpp
        Abstract/AbstractGUI.cpp

        # GAME
        Game/GameManager.cpp
        Game/GameUI.cpp
        Game/GameGUI.cpp

        # ENTITIES
        Entities/Snake.cpp
        Entities/Food.cpp

        Position.hpp

        # TOOLS
        Tools/Constants.hpp
        Tools/Ressources.hpp)

add_executable(Snake ${SOURCE_FILES})
target_link_libraries(Snake ncurses SDL2 SDL2_image)