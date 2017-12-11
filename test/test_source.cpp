#include "../lib/gtest-1.7.0/include/gtest/gtest.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "test_types.cpp"
#include "../src/engine.h"
#include "../src/Graphics/graphicsEngine.h"

// Initial values
const int initial_money = 600;
const double timestep = 0.01;
const int initial_lives = 10;

// Tower type instances
// Enemy type instances
auto enemy_type_1 = EnemyType1();
auto enemy_type_2 = EnemyType2();

auto empty_tower_type = EmptyTowerType();
auto root_tower_type = RootTowerType();

auto tower_type_a = TowerTypeA();
auto tower_type_a2 = TowerTypeA2();

auto tower_type_b = TowerTypeB();
auto tower_type_b2 = TowerTypeB2();
auto tower_type_b3 = TowerTypeB3();

EnemySpawnInterval enemy_spawn_interval = {
    {4.0, &enemy_type_1},
    {8.0, &enemy_type_2},
    {13.0, &enemy_type_2},
    {18.0, &enemy_type_2},
    {21.0, &enemy_type_2}
};

TEST(initialization, tower_options) {
	root_tower_type.add_upgrade_option(&tower_type_a);
	tower_type_a.add_upgrade_option(&tower_type_a2);
	root_tower_type.add_upgrade_option(&tower_type_b);
	tower_type_b.add_upgrade_option(&tower_type_b2);
	tower_type_b.add_upgrade_option(&tower_type_b3);
}

TEST(initialization, GameMap) {
	//std::cout << "Initializing GameMap" << std::endl;
	auto game_map = game_map_from_file("../src/maps/map1.txt", &empty_tower_type, &root_tower_type);
	auto game_map2 = game_map_from_file("../src/maps/map2.txt", &empty_tower_type, &root_tower_type);

}

TEST(initialization, GameLevel) {
	//std::cout << "Initializing GameLevel" << std::endl;
	auto game_level = GameLevel(initial_money, 0, 0, enemy_spawn_interval);
}

TEST(initialization, GameEngine) {
	//std::cout << "Initializing GameEngine" << std::endl;
	auto game_map = game_map_from_file("../src/maps/map2.txt", &empty_tower_type, &root_tower_type);
	auto game_level = GameLevel(initial_money, 0, 0, enemy_spawn_interval);
	auto game_engine = new GameEngine(0, timestep, 0, game_level, game_map);
}
