#ifndef TOWER_DEFENCE_2_TOWER_H
#define TOWER_DEFENCE_2_TOWER_H

#include "object.h"


/// Base class for all towers.
class TowerBase : public Object {
public:
    TowerBase(int x, int y, int radius, int health, int damage,
              int attack_range, int attack_speed, int cost, int repair_cost,
              int upgrade_cost);

    /// Repairs the tower. Changes the health of the tower to full health and
    /// reduces player's money accordingly.
    /// Return the cost of the repair.
    int repair();

    /// Upgrade the tower. Returns a pointer to the new tower instance.
    TowerBase* upgrade();

protected:
    int m_cost;
    int m_repair_cost;
    int m_upgrade_cost;
    //TODO: upgrade options as container of tower classes, maybe enum?
};


#endif //TOWER_DEFENCE_2_TOWER_H
