cmake_minimum_required(VERSION 3.7)
project(Snake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Snake_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${Snake_SOURCE_DIR}/source/headers)

set(SOURCE_FILES main.cpp)
add_executable(Snake ${SOURCE_FILES})
target_link_libraries(Snake ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})