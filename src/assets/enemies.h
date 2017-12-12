#ifndef TOWER_DEFENCE_2_ENEMIES_H
#define TOWER_DEFENCE_2_ENEMIES_H

#include <iostream>
#include "../objects/enemy.h"


class EnemyType1 : public EnemyType {
public:
    EnemyType1() : EnemyType("Enemy1", 50, 100, 0.5, 1000) { }
};

class EnemyType2 : public EnemyType {
public:
    EnemyType2() : EnemyType("Enemy2", 40, 110, 0.35, 1000) { }
};

class EnemyType3 : public EnemyType {
public:
    EnemyType3() : EnemyType("Enemy2", 60, 200, 0.45, 2000) { }
};

#endif //TOWER_DEFENCE_2_ENEMIES_H
