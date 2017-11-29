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
    EnemyType1() : EnemyType("Enemy1", 50, 100, 1, 40) { }
};

/// for test..
void printhp(GameMap map) {
    auto it = map.enemies().begin();
    it++;
    while (it != map.enemies().end()) {
        std::cout << (*it)->health() << "  ";
        it++;
    }
    std::cout << std::endl;
}

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
    Tower t1 = tower_type_1.create_tower(0, 1);
    Tower t2 = tower_type_1.create_tower(1, 1);
    Tower t3 = tower_type_2.create_tower(2, 1);
    game_map.set_tower(&t1);
    game_map.set_tower(&t2);
    game_map.set_tower(&t3);
    game_map.get_tile(0, 1)->set_tower(&t1);
    game_map.get_tile(0, 1)->set_tower(&t2);
    game_map.get_tile(0, 1)->set_tower(&t3);

    Enemy e1 = enemy_type_1.create_enemy(3, 0);
    Enemy e2 = enemy_type_1.create_enemy(3, 1);
    Enemy e3 = enemy_type_1.create_enemy(3, 2);
    game_map.set_enemy(&e1);
    game_map.set_enemy(&e2);
    game_map.set_enemy(&e3);


    std::cout << "Initializing GameLevel" << std::endl;
    std::vector<int> enemy_spawn_interval = {};
    auto game_level = GameLevel(1000, 0, enemy_spawn_interval);

    std::cout << "Initializing GameStats" << std::endl;
    auto game_stats = GameStats(0, 0, 0);

    std::cout << "Initializing GameEngine" << std::endl;
    auto game_engine = GameEngine(game_stats, game_map, game_level);
/*
    std::cout << "Tower attack test.." << std::endl;
    printhp(game_map);
    game_engine.towers_attack();
    printhp(game_map);
*/



}
