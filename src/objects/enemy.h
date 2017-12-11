#ifndef TOWER_DEFENCE_2_ENEMY_H
#define TOWER_DEFENCE_2_ENEMY_H

#include "object.h"
#include <string>


// Deferred declaration
class EnemyType;

/// Enemy class
class Enemy : public Object {
public:
    Enemy(double x, double y, double radius, double speed, int health,
          EnemyType *enemy_type);
    ~Enemy();

    int score() const;
    int money() const;

private:
    EnemyType *m_enemy_type;
};

/// Description for creating new enemies
class EnemyType {
public:
    EnemyType(const std::string &name, int score, int money, double speed,
              int health);

    ~EnemyType();

    int score() const;
    int money() const;

    /// Create new enemy of this type.
    Enemy * create_enemy(double x, double y);

private:
    /// Name of the enemy
    const std::string m_name;

    /// Amount of score that is awarded to the player when enemy dies
    const int m_score;

    /// Amount of money that is awarded to the player when enemy dies
    const int m_money;

    // Initial values for new enemies
    const double m_speed;
    const int m_health;
};


#endif //TOWER_DEFENCE_2_ENEMY_H
