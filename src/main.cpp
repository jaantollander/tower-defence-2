#include <iostream>
#include "game.h"

/// Main program.
/// 1) Initialize game stats
///     - Starting money
/// 2) Initialize game map
///     - Load from file
/// 3) Initialize game engine
/// 4) Initialize graphics engine
int main() {
    std::cout << "Initializing GameStats" << std::endl;
    auto stats = GameStats(0, 0, 1000);

    std::cout << "Initializing GameMap" << std::endl;


}
