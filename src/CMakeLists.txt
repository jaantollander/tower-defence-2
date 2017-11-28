cmake_minimum_required(VERSION 3.8)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Graphics/graphicsFunctions.cpp
        Graphics/graphicsFunctions.h
        Graphics/graphicsTest.cpp
        objects/combat.cpp
        objects/combat.h
        objects/enemy.cpp
        objects/enemy.h
        objects/object.cpp
        objects/object.h
        objects/tower.cpp
        objects/tower.h
        engine.cpp
        engine.h
        level.cpp
        level.h
        main.cpp
        map.cpp
        map.h
        tile.cpp
        tile.h towers/testtower.h towers/testtower.cpp towers/test2.h towers/test2.cpp)

add_executable(src ${SOURCE_FILES})