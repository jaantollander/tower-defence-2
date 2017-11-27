#include <iostream>
#include "engine.h"


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


class TowerType1 : public TowerType {
public:
    TowerType1() : TowerType("Tower1", 300, 20, 4, 8) { }
};


class TowerType2 : public TowerType {
public:
    TowerType2() : TowerType("Tower2", 100, 10, 4, 5) { }
};


class EnemyType1 : public EnemyType {
public:
    EnemyType1() : EnemyType("Enemy1", 50, 100, 1, 10) { }
};


/// Run tower defence game. Currently used for testing.
int main() {
    auto empty_tower_type = EmptyTowerType();
    auto tower_type_1 = TowerType1();
    auto tower_type_2 = TowerType2();
    auto enemy_type_1 = EnemyType1();

    //TODO: upgrade options

    //TODO: initialize tile with empty tower type
    std::cout << "Initializing GameMap" << std::endl;
    auto game_map = game_map_from_file("src/maps/example.txt");
    std::cout << "Load done.." << std::endl;
    std::cout << game_map;

    //TODO: add towers and enemies

    std::cout << "Initializing GameLevel" << std::endl;
    std::vector<int> enemy_spawn_interval = {};
    auto game_level = GameLevel(1000, 0, enemy_spawn_interval);

    std::cout << "Initializing GameStats" << std::endl;
    auto game_stats = GameStats(0, 0, 0);

    std::cout << "Initializing GameEngine" << std::endl;
    auto game_engine = GameEngine(game_stats, game_map, game_level);

    Tower


}
