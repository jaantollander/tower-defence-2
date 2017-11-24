#ifndef TOWER_DEFENCE_2_ENEMY_H
#define TOWER_DEFENCE_2_ENEMY_H

#include "object.h"
#include <string>


// Deferred declaration
class EnemyType;


/// Enemy class
class Enemy : public Object {
public:
    Enemy(int x, int y, int radius, int speed, int health,
          EnemyType *enemy_type);
    ~Enemy();

private:
    EnemyType *m_enemy_type;
};


/// Description for creating new enemies
class EnemyType {
public:
    EnemyType(const std::string &name, int score, int money, int speed,
                  int health);

    ~EnemyType();

    /// Create new enemy of this type.
    Enemy create_enemy(int x, int y);

private:
    /// Name of the enemy
    const std::string m_name;

    /// Amount of score that is awarded to the player when enemy dies
    const int m_score;

    /// Amount of money that is awarded to the player when enemy dies
    const int m_money;

    // Initial values for new enemies
    const int m_speed;
    const int m_health;
};


#endif //TOWER_DEFENCE_2_ENEMY_H
