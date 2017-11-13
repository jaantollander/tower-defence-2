#include "enemy.h"


EnemyBase::EnemyBase(int x, int y, int radius, int speed, int health,
                     int damage, int attack_range, int attack_speed) :
        Object(x, y, radius, speed),
        Combat(health, damage, attack_range, attack_speed) {}
