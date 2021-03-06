#ifndef TOWER_DEFENCE_2_TOWERS_H
#define TOWER_DEFENCE_2_TOWERS_H

#include <iostream>
#include "../objects/tower.h"

#define MULTIPLIER_2 0.82

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


/// Towers of the game. Towers are upgraded using a linear upgrade path.
/// As the tower is upgraded, it get better damage, range and fire rate.
/// The game should be somewhat balanced so that it's possible to win but
/// also possible to lose.

class TowerTypeA : public TowerType {
public:
    TowerTypeA() : TowerType("Tower1", 100, 8, 3.0, 1.9 * MULTIPLIER_2) { }
};

class TowerTypeA2 : public TowerType {
public:
    TowerTypeA2() : TowerType("Tower2", 80, 15, 3.4, 1.6 * MULTIPLIER_2) { }
};

class TowerTypeB : public TowerType {
public:
    TowerTypeB() : TowerType("TowerTypeB", 120, 24, 4.0, 1.4 * MULTIPLIER_2) { }
};

class TowerTypeB2 : public TowerType {
public:
    TowerTypeB2() : TowerType("TowerTypeB2", 180, 32, 4.0, 1.25 * MULTIPLIER_2) { }
};



#endif //TOWER_DEFENCE_2_TOWERS_H
