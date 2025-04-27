cmake_minimum_required(VERSION 3.31)
project(Game)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(MyPotatoGame
        src_1/main.cpp
        src_1/Player.cpp
)

target_link_libraries(MyPotatoGame PRIVATE SFML::Graphics SFML::Window SFML::System)