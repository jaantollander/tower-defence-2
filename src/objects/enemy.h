#ifndef TOWER_DEFENCE_2_ENEMY_H
#define TOWER_DEFENCE_2_ENEMY_H

#include "object.h"


/// Base class for all enemy types.
class EnemyBase : public Object {
public:
    EnemyBase(int x, int y, int radius, int speed, int health, int damage,
                  int attack_range, int attack_speed, int score);

    /// Score that player get when enemy dies.
    int score();

protected:
    int m_score;
};

#endif //TOWER_DEFENCE_2_ENEMY_H
