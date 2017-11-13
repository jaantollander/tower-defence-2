#include "tower.h"

TowerBase::TowerBase(int x, int y, int radius, int health, int damage,
                     int attack_range, int attack_speed, int cost,
                     int repair_cost, int upgrade_cost) :
        Object(x, y, radius, 0),
        Combat(health, damage, attack_range, attack_speed),
        m_cost(cost),
        m_repair_cost(repair_cost),
        m_upgrade_cost(upgrade_cost) {}
