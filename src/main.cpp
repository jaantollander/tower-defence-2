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
    EnemyType1() : EnemyType("Enemy1", 50, 100, 1, 40) { }
};


class EnemyType2 : public EnemyType {
public:
    EnemyType2() : EnemyType("Enemy2", 0, 0, 0, 0) { }
};


void printhp(GameMap map) {
    size_t size = map.enemies().size();
    int i = 0;
    while (i < size) {
        std::cout << map.enemies()[i] -> health() << "  ";
        i++;
    }
    std::cout << std::endl;
}


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
    auto enemy_type_2 = EnemyType2();

    std::cout << "Initializing GameMap" << std::endl;
    sep();
    auto game_map = game_map_from_file(
            "../src/maps/example.txt", &empty_tower_type, &root_tower_type);
    std::cout << game_map << std::endl;


    //FIXME: Change to use upgrade mechanics
//    Tower t1 = tower_type_1.create_tower(0, 1);
//    Tower t2 = tower_type_1.create_tower(1, 1);
//    Tower t3 = tower_type_2.create_tower(2, 1);
//    game_map.set_tower(&t1);
//    game_map.set_tower(&t2);
//    game_map.set_tower(&t3);
//    game_map.get_tile(0, 1)->set_tower(&t1);
//    game_map.get_tile(1, 1)->set_tower(&t2);
//    game_map.get_tile(2, 1)->set_tower(&t3);
//
//
//    Enemy e1 = enemy_type_1.create_enemy(3, 0);
//    Enemy e2 = enemy_type_1.create_enemy(3, 1);
//    Enemy e3 = enemy_type_1.create_enemy(3, 2);
//    game_map.set_enemy(&e1);
//    game_map.set_enemy(&e2);
//    game_map.set_enemy(&e3);


    std::cout << "Initializing GameLevel" << std::endl;
    sep();
    EnemySpawnInterval enemy_spawn_interval = {
            {1.0, &enemy_type_1},
            {2.0, &enemy_type_2}
    };
    auto game_level = GameLevel(1000, 0, 0, enemy_spawn_interval);


    std::cout << "Initializing GameEngine" << std::endl;
    sep();
    auto game_engine = GameEngine(0, 0.01, 0, 0, 10, game_level, game_map);

//    std::cout << "Tower attack test.." << std::endl;
//    printhp(game_map);
//    game_engine.towers_attack();
//    printhp(game_map);




}
