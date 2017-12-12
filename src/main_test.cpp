#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "engine.h"
#include "Graphics/graphicsEngine.h"


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


int main() {
    // Enemy type instances
    auto enemy_type_1 = EnemyType1();
    auto enemy_type_2 = EnemyType2();

    // Initial values
    int initial_money = 600;
    double timestep = 0.01;
    int initial_lives = 10;

    EnemySpawnInterval enemy_spawn_interval = {
            {0.0, &enemy_type_1},
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

    // Define tower hierarchy (upgrade options)
    root_tower_type.add_upgrade_option(&tower_type_a);
    tower_type_a.add_upgrade_option(&tower_type_a2);
    tower_type_a2.add_upgrade_option(&tower_type_b);
    tower_type_b.add_upgrade_option(&tower_type_b2);
    tower_type_b2.add_upgrade_option(&tower_type_b3);


    auto game_map = game_map_from_file(
            "../src/assets/map1.txt", &empty_tower_type, &root_tower_type);
    auto game_level = GameLevel(initial_money, initial_lives, 0, enemy_spawn_interval);
    auto game_engine = new GameEngine(0, timestep, 0, game_level, game_map);

    for (int i = 0; i < 1000; ++i) {
        game_engine->update();
    }

}

