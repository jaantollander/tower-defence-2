#include <iostream>
#include "../src/objects/object.h"
#include "../src/objects/enemy.h"
#include "../src/objects/tower.h"


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

