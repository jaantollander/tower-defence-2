#include "../lib/gtest-1.7.0/include/gtest/gtest.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "../src/engine.h"
#include "../src/Graphics/graphicsEngine.h"


TEST(test_test, test_test) {
    EXPECT_EQ(1, 1);
}

/// Empty tower type. Cannot be upgraded into any tower.
class EmptyTowerType : public TowerType {
public:
    EmptyTowerType() : TowerType("EmptyTower", 0, 0, 0, 0) { }
};


/// Empty tower type. Can be upgraded into a tower defined by upgrade options.
class RootTowerType : public TowerType {
public:
    RootTowerType() : TowerType("RootTower", 0, 0, 0, 0) { }
};


class TowerTypeA : public TowerType {
public:
    TowerTypeA() : TowerType("Tower1", 100, 10, 2.0, 2.0) { }
};


class TowerTypeA2 : public TowerType {
public:
    TowerTypeA2() : TowerType("Tower2", 100, 15, 2.0, 1.5) { }
};


class TowerTypeB : public TowerType {
public:
    TowerTypeB() : TowerType("TowerTypeB", 100, 5, 4.0, 2.0) { }
};


class TowerTypeB2 : public TowerType {
public:
    TowerTypeB2() : TowerType("TowerTypeB2", 150, 10, 4.0, 1.0) { }
};


class TowerTypeB3 : public TowerType {
public:
    TowerTypeB3() : TowerType("TowerTypeB3", 150, 20, 5.0, 2.0) { }
};


class EnemyType1 : public EnemyType {
public:
    EnemyType1() : EnemyType("Enemy1", 50, 100, 0.5, 100) { }
};


class EnemyType2 : public EnemyType {
public:
    EnemyType2() : EnemyType("Enemy2", 40, 110, 0.1, 100) { }
};

void sep(int length=80) {
    for (int i = 0; i < length; ++i) { std::cout <<  '='; }
    std::cout << std::endl;
}


class td_test : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.
	
	td_test() {
		// Enemy type instances
		auto enemy_type_1 = EnemyType1();
		auto enemy_type_2 = EnemyType2();

		// Initial values
		int initial_money = 1000;
		double timestep = 0.01;
		int lives = 10;

		EnemySpawnInterval enemy_spawn_interval = {
		    {1.0, &enemy_type_1},
		    {2.0, &enemy_type_2}
		};

		// Tower type instances
		auto empty_tower_type = EmptyTowerType();
		auto root_tower_type = RootTowerType();

		auto tower_type_a = TowerTypeA();
		auto tower_type_a2 = TowerTypeA2();

		auto tower_type_b = TowerTypeB();
		auto tower_type_b2 = TowerTypeB2();
		auto tower_type_b3 = TowerTypeB3();

		// Upgrade options
		root_tower_type.add_upgrade_option(&tower_type_a);
		tower_type_a.add_upgrade_option(&tower_type_a2);
		root_tower_type.add_upgrade_option(&tower_type_b);
		tower_type_b.add_upgrade_option(&tower_type_b2);
		tower_type_b.add_upgrade_option(&tower_type_b3);


		//std::cout << "Initializing GameMap" << std::endl;
		//sep();
		auto game_map = game_map_from_file(
		    "../src/maps/map2.txt", &empty_tower_type, &root_tower_type);
		//std::cout << game_map << std::endl;

		//std::cout << "Initializing GameLevel" << std::endl;
		//sep();
		auto game_level = GameLevel(initial_money, 0, 0, enemy_spawn_interval);

		//std::cout << "Initializing GameEngine" << std::endl;
		//sep();
		auto game_engine = new GameEngine(0, timestep, 0, 0, lives, game_level, game_map);

		// Set towers
		//TODO: remove this eventually when gui is ready.
		game_engine->upgrade_tower(0, 0, 0);
		game_engine->upgrade_tower(1, 1, 1);
		game_engine->upgrade_tower(2, 2, 1);	
	}

	virtual ~td_test() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	EmptyTowerType * empty_tower_type;
	RootTowerType * root_tower_type;

};


TEST_F(td_test, initialization_load_map) {

	game_map_from_file("../src/maps/map2.txt", empty_tower_type, root_tower_type);
	game_map_from_file("../src/maps/map1.txt", empty_tower_type, root_tower_type);

	EXPECT_EQ(1, 1);
}



/*
cmake .. -Dtest=ON
make
./UnitTests

// The fixture for testing class Project1. From google test primer.
class Project1Test : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	Project1Test() {
		// You can do set-up work for each test here.
	}

	virtual ~Project1Test() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Project1.
	Project1 p;
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(Project1Test, MethodBarDoesAbc) {
	int i = 0;
	p.foo(i); // we have access to p, declared in the fixture
	EXPECT_EQ(1, i);
}

// }  // namespace - could surround Project1Test in a namespace
*/

