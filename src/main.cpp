#include <iostream>
#include "engine.h"


/// Run tower defence game. Currently used for testing.
int main() {
    std::cout << "Initializing GameMap" << std::endl;
    auto game_map = load_game_map("../src/maps/testmap1");

    game_map.print_map();

    std::cout << "Initializing GameLevel" << std::endl;
    std::vector<int> enemy_spawn_interval = {};
    auto game_level = GameLevel(1000, 0, enemy_spawn_interval);

    std::cout << "Initializing GameStats" << std::endl;
    auto game_stats = GameStats(0, 0, 0);

    std::cout << "Initializing GameEngine" << std::endl;
    auto game_engine = GameEngine(game_stats, game_map, game_level);

}
