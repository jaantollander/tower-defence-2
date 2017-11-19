#include "enemy.h"


EnemyBase::EnemyBase(int x, int y, int radius, int speed, int health, int damage,
                     int attack_range, int attack_speed, int score) :
        Object(x, y, radius, speed),
        Combat(health, damage, attack_range, attack_speed),
        m_score(score) {}


int EnemyBase::score() { return m_score; }
