#ifndef TOWER_DEFENCE_2_ENEMY_H
#define TOWER_DEFENCE_2_ENEMY_H

#include "object.h"
#include <string>


//TODO: EnemyOption


/// Base class for all enemy types.
class Enemy : public Object {
public:
    Enemy(int x, int y, int radius, int speed, int health, int damage,
          int attack_range, int attack_speed, int score);

    int score();
    int money();

protected:
//    Object m_object;

    /// Name of the enemy
    std::string m_name;

    /// Amount of score that is awarded to the player when enemy dies
    int m_score;

    /// Amount of money that is awarded to the player when enemy dies
    int m_money;
};


#endif //TOWER_DEFENCE_2_ENEMY_H
