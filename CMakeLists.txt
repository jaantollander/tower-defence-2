cmake_minimum_required(VERSION 3.5)
project(tower_defence_2)

set(CMAKE_CXX_STANDARD 11)
#TODO: CXX_FLAGS, flags for graphics

add_executable(
        tower_defence_2
        src/geom2D.cpp
        src/objects/object.cpp
        src/objects/enemy.cpp
        src/objects/tower.cpp
        src/level.cpp
        src/tile.cpp
        src/tiles.cpp
        src/path.cpp
        src/map.cpp
        src/engine.cpp
        src/main.cpp
)
