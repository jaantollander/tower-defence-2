#ifndef TOWER_DEFENCE_2_ENEMIES_H
#define TOWER_DEFENCE_2_ENEMIES_H

#include <iostream>
#include "../objects/enemy.h"

#define MULTIPLIER 1.2

class EnemyType1 : public EnemyType {
public:
    EnemyType1() : EnemyType("Basic", 12, 12, 0.5 * MULTIPLIER, 120) { }
};

class EnemyType2 : public EnemyType {
public:
    EnemyType2() : EnemyType("Tank", 35, 35, 0.30 * MULTIPLIER, 450) { }
};

class EnemyType3 : public EnemyType {
public:
    EnemyType3() : EnemyType("Runner", 25, 25, 0.75 * MULTIPLIER, 100) { }
};

class EnemyType4 : public EnemyType {
public:
    EnemyType4() : EnemyType("Lord", 60, 60, 0.6 * MULTIPLIER, 400) { }
};

class EnemyType5 : public EnemyType {
public:
    EnemyType5() : EnemyType("The King", 100, 100, 0.55 * MULTIPLIER, 700) { }
};

#endif //TOWER_DEFENCE_2_ENEMIES_H
