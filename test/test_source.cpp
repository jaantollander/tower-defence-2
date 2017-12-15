#include "../lib/gtest-1.7.0/include/gtest/gtest.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>


#include "../src/engine.h"
#include "../src/Graphics/graphicsEngine.h"

#include "../src/assets/towers.h"
#include "../src/assets/enemies.h"
  
TEST(initialization, tower_initialization) {
	EnemyType1();
	EnemyType2();
	EnemyType3();
	EmptyTowerType();
	RootTowerType();
	TowerTypeA();
	TowerTypeA2();
	TowerTypeB();
	TowerTypeB2();
}

// Test tower type instances & Enemy type instances
auto enemy_type_1 = EnemyType1();
auto enemy_type_2 = EnemyType2();
auto enemy_type_3 = EnemyType3();

auto empty_tower_type = EmptyTowerType();
auto root_tower_type = RootTowerType();

auto tower_type_a = TowerTypeA();
auto tower_type_a2 = TowerTypeA2();

auto tower_type_b = TowerTypeB();
auto tower_type_b2 = TowerTypeB2();

TEST(initialization, tower_options) {
	root_tower_type.add_upgrade_option(&tower_type_a);
	tower_type_a.add_upgrade_option(&tower_type_a2);
	root_tower_type.add_upgrade_option(&tower_type_b);
	tower_type_b.add_upgrade_option(&tower_type_b2);
}

TEST(initialization, GameMap) {

	game_map_from_file("../src/assets/map1.txt", &empty_tower_type, &root_tower_type);
	game_map_from_file("../src/assets/map2.txt", &empty_tower_type, &root_tower_type);

	//ASSERT_ANY_THROW(game_map_from_file("NotExistingMap.txt", &empty_tower_type, &root_tower_type));
	ASSERT_THROW(game_map_from_file("NotExistingMap.txt", &empty_tower_type, &root_tower_type), std::exception);

}

// Test values
EnemySpawnInterval enemy_spawn_interval = {
    {4.0, &enemy_type_1},
    {8.0, &enemy_type_2},
    {13.0, &enemy_type_3},
    {18.0, &enemy_type_1},
    {21.0, &enemy_type_2},
    {23.0, &enemy_type_3},
    {25.0, &enemy_type_1},
    {27.0, &enemy_type_2},
    {28.0, &enemy_type_3},
    {29.0, &enemy_type_2},
};

EnemySpawnInterval test_enemy_spawn_interval = {
    {1.0, &enemy_type_1},
    {2.0, &enemy_type_2},
    {3.0, &enemy_type_3},
};

int initial_money = 600;
int initial_money2 = 100;
int initial_money3 = 1000;

double timestep = 0.01;
int initial_lives = 5;
int initial_lives2 = 10;

TEST(initialization, GameLevel) {
	GameLevel(initial_money, 0, 0, enemy_spawn_interval);
	GameLevel(initial_money2, 0, 0, enemy_spawn_interval);
	GameLevel(initial_money3, 0, 0, test_enemy_spawn_interval);
}


TEST(initialization, GameEngine) {
	auto game_map = game_map_from_file("../src/assets/map1.txt", &empty_tower_type, &root_tower_type);
	auto game_level1 = GameLevel(initial_money, 0, 0, enemy_spawn_interval);
	auto game_level2 = GameLevel(initial_money3, 0, 0, test_enemy_spawn_interval);

	new GameEngine(0, timestep, 0, game_level1, game_map);
	new GameEngine(0, timestep, 0, game_level2, game_map);
	
}

auto game_map = game_map_from_file("../src/assets/map1.txt", &empty_tower_type, &root_tower_type);
auto game_level = GameLevel(25, initial_lives, 0, enemy_spawn_interval);
auto test_game_engine = new GameEngine(0, timestep, 0, game_level, game_map);

TEST(Game_engine, money) {

	ASSERT_TRUE(test_game_engine->add_money(25));
	ASSERT_EQ(test_game_engine->add_money(150),true);
	ASSERT_EQ(test_game_engine->add_money(250),true);
	ASSERT_EQ(test_game_engine->money(), 450);
	
	ASSERT_EQ(test_game_engine->add_money(-450),true);
	ASSERT_EQ(test_game_engine->add_money(-1), false);
	ASSERT_EQ(test_game_engine->money(), 0);
	
}

TEST(Game_engine, score_life) {
	
	// Test lives
	ASSERT_EQ(test_game_engine->lives(),5);
	
	test_game_engine->reduce_life() ;
	test_game_engine->reduce_life() ;
	test_game_engine->reduce_life() ;
	test_game_engine->reduce_life() ;

	ASSERT_EQ(test_game_engine->lives(), 1);
	
	// Test score
	ASSERT_EQ(test_game_engine->score(), 0);

	test_game_engine->add_score(150);
	test_game_engine->add_score(25);
	test_game_engine->add_score(75);
	ASSERT_EQ(test_game_engine->score(), 250);
	
	// Score cant go below 0
	test_game_engine->add_score(-300);
	ASSERT_EQ(test_game_engine->score(), 0);


}


/// Initialize new game engine
enum MapChoices {
    map1,
    map2
};

GameEngine *new_game_engine(MapChoices map_choice, TowerType *empty_tower_type,
        TowerType *root_tower_type, int initial_money, int initial_lives,
        EnemySpawnInterval &enemy_spawn_interval, double timestep) {
    std::string map_path;
    switch (map_choice) {
        case map1: {
            map_path = "../src/assets/map1.txt";
            break;
        }
        case map2: {
            map_path = "../src/assets/map2.txt";
            break;
        }
        default:
            throw std::exception();
    }
    auto game_map = game_map_from_file(map_path, empty_tower_type, root_tower_type);
    auto game_level = GameLevel(initial_money, initial_lives, 0, enemy_spawn_interval);
    return new GameEngine(0, timestep, 0, game_level, game_map);
}


TEST(Game_map, map_path_tiles) {

	auto test_map = test_game_engine->game_map();
	ASSERT_EQ(test_map.name(),"example");

	auto test_path = test_map.path();


	ASSERT_TRUE(1000 > test_path.get_length() > 0);
	ASSERT_TRUE( 1000 > test_path.distance_from_end(0) > 0);
	ASSERT_EQ(test_path.distance_from_end(test_path.get_length()), 0);
	//has_reached_end(double d)
	ASSERT_TRUE(test_path.has_reached_end(test_path.get_length()));
	ASSERT_FALSE(test_path.has_reached_end(test_path.get_length()-1));
	//TODO test tiles and path

	auto test_tiles = test_map.tiles();
	ASSERT_TRUE(0<test_tiles.xsize<50);
	ASSERT_TRUE(0<test_tiles.ysize<50);
	ASSERT_TRUE(0<test_tiles.tilesize<50);

	auto test_tile1 = *test_tiles.tile(0,0);
	auto test_tile2 = *test_tiles.tile(test_tiles.xsize-1, test_tiles.ysize-1);
	std::cout << "tile types:" << test_tile1.tile_type() <<" "<< test_tile2.tile_type() <<std::endl;

}


TEST(Game_map, print_map) {
	auto test_map = test_game_engine->game_map();
	std::cout << test_map << std::endl;
}



TEST(Game_map, enemies) {
	auto test_map = test_game_engine->game_map();

	auto test_enemy1 = Enemy(1, 2, 3,4, 5, &enemy_type_1 );
	auto test_enemy2 = Enemy(6, 7, 8, 9, 10, &enemy_type_2 );

	test_map.add_enemy(&test_enemy1);
	test_map.add_enemy(&test_enemy2);
	auto test_enemies = test_map.enemies();

	ASSERT_EQ(test_enemies.size(), 2);

}


TEST(Game_map, update) {
	auto test_map = test_game_engine->game_map();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
	graphicsEngine gE = graphicsEngine(window);
	auto state = test_game_engine->update(gE);
	
	test_game_engine->reduce_life() ;
	ASSERT_EQ(state, 0);

	auto state2 = test_game_engine->update(gE);

	ASSERT_EQ(state2, 2);

}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	std::cout<<"Running all tests"<<std::endl;

	return RUN_ALL_TESTS();

}
