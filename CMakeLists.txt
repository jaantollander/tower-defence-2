cmake_minimum_required(VERSION 3.5)
project(tower_defence_2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "")
set(EXECUTABLE_OUTPUT_PATH ../build)

# Build tests with cmake -Dtest=ON
option(test "Build all tests." OFF)

add_executable(
        tower_defence_2
        src/geom2D.cpp
        src/objects/object.cpp
        src/objects/enemy.cpp
        src/objects/tower.cpp
        src/level.cpp
        src/map/tile.cpp
        src/map/tiles.cpp
        src/map/path.cpp
        src/map/map.cpp
        src/engine.cpp
        src/Graphics/graphicsButton.cpp
        src/Graphics/graphicsFunctions.cpp
        src/Graphics/graphicsEngine.cpp
        src/main.cpp
)

target_link_libraries(tower_defence_2 sfml-graphics sfml-window sfml-system)

if (test)
    # This adds another subdirectory, which has 'project(gtest)'.
    add_subdirectory(lib/gtest-1.7.0)

    enable_testing()

    # Include the gtest library. gtest_SOURCE_DIR is available due to
    # 'project(gtest)' above.
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    ##############
    # Unit Tests
    ##############
    add_executable(
            UnitTests
        src/geom2D.cpp
        src/objects/object.cpp
        src/objects/enemy.cpp
        src/objects/tower.cpp
        src/level.cpp
        src/map/tile.cpp
        src/map/tiles.cpp
        src/map/path.cpp
        src/map/map.cpp
        src/engine.cpp
        src/Graphics/graphicsButton.cpp
        src/Graphics/graphicsFunctions.cpp
        src/Graphics/graphicsEngine.cpp
        test/test_source.cpp
    )

    # Standard linking to gtest stuff.
    target_link_libraries(UnitTests gtest gtest_main)
    # Extra linking for the project.
    target_link_libraries(UnitTests sfml-graphics sfml-window sfml-system)

    # This is so you can do 'make test' to see all your tests run, instead of
    # manually running the executable runUnitTests to see those specific tests.
    add_test(NAME test COMMAND UnitTests)

endif()
