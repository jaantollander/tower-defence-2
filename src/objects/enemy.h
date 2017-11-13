#ifndef TOWER_DEFENCE_2_ENEMY_H
#define TOWER_DEFENCE_2_ENEMY_H

#include "combat.h"
#include "object.h"


/// Base class for all enemy types.
class EnemyBase : public Object, public Combat {
public:
    EnemyBase(int x, int y, int radius, int speed, int health, int damage,
              int attack_range, int attack_speed);
};

#endif //TOWER_DEFENCE_2_ENEMY_H
