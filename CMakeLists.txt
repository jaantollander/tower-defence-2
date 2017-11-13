cmake_minimum_required(VERSION 3.9)
project(tower_defence_2)

set(CMAKE_CXX_STANDARD 11)
#TODO: CXX_FLAGS

add_executable(
        tower_defence_2
        src/objects/object.cpp
        src/objects/combat.cpp
        src/objects/enemy.cpp
        src/objects/tower.cpp
        src/game.cpp
        src/main.cpp
)
