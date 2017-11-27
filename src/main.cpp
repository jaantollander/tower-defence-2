#include <iostream>
#include "engine.h"


//TODO: move empty and root tower types into object/tower


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
    TowerTypeA() : TowerType("Tower1", 300, 20, 4, 8) { }
};


class TowerTypeA2 : public TowerType {
public:
    TowerTypeA2() : TowerType("Tower2", 0, 0, 0, 0) { }
};


class TowerTypeB : public TowerType {
public:
    TowerTypeB() : TowerType("TowerTypeB", 100, 10, 4, 5) { }
};


class TowerTypeB2 : public TowerType {
public:
    TowerTypeB2() : TowerType("TowerTypeB2", 0, 0, 0, 0) { }
};


class TowerTypeB3 : public TowerType {
public:
    TowerTypeB3() : TowerType("TowerTypeB3", 0, 0, 0, 0) { }
};


class EnemyType1 : public EnemyType {
public:
    EnemyType1() : EnemyType("Enemy1", 50, 100, 1, 10) { }
};


void sep(int length=80) {
    for (int i = 0; i < length; ++i) { std::cout <<  '='; }
    std::cout << std::endl;
}


/// Run tower defence game. Currently used for testing.
int main() {
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

    // Enemy type instances
    auto enemy_type_1 = EnemyType1();

    //TODO: initialize tile with empty or root tower type
    //TODO: add towers and enemies

    std::cout << "Initializing GameMap" << std::endl;
    sep();
    auto game_map = game_map_from_file("../src/maps/example.txt");
    std::cout << game_map << std::endl;

    std::cout << "Initializing GameLevel" << std::endl;
    sep();
    std::vector<int> enemy_spawn_interval = {};
    auto game_level = GameLevel(1000, 0, enemy_spawn_interval);

    std::cout << "Initializing GameStats" << std::endl;
    sep();
    auto game_stats = GameStats(0, 0, 0);

    std::cout << "Initializing GameEngine" << std::endl;
    sep();
    auto game_engine = GameEngine(game_stats, game_map, game_level);

}
