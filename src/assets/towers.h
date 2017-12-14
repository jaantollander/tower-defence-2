#ifndef TOWER_DEFENCE_2_TOWERS_H
#define TOWER_DEFENCE_2_TOWERS_H

#include <iostream>
#include "../objects/tower.h"

#define MULTIPLIER 0.8

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
    TowerTypeA() : TowerType("Tower1", 100, 8, 3.0, 1.9 * MULTIPLIER) { }
};

class TowerTypeA2 : public TowerType {
public:
    TowerTypeA2() : TowerType("Tower2", 80, 15, 3.4, 1.6 * MULTIPLIER) { }
};

class TowerTypeB : public TowerType {
public:
    TowerTypeB() : TowerType("TowerTypeB", 120, 24, 4.0, 1.4 * MULTIPLIER) { }
};

class TowerTypeB2 : public TowerType {
public:
    TowerTypeB2() : TowerType("TowerTypeB2", 180, 32, 4.0, 1.25 * MULTIPLIER) { }
};

//Last one is unused
class TowerTypeB3 : public TowerType {
public:
    TowerTypeB3() : TowerType("TowerTypeB3", 150, 20, 5.0, 2.0) { }
};


#endif //TOWER_DEFENCE_2_TOWERS_H
