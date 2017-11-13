#ifndef TOWER_DEFENCE_2_TOWER_H
#define TOWER_DEFENCE_2_TOWER_H

#include "combat.h"
#include "object.h"


/// Base class for all towers.
class TowerBase : public Object, public Combat {
public:
    TowerBase(int x, int y, int radius, int health, int damage,
              int attack_range, int attack_speed, int cost, int repair_cost,
              int upgrade_cost);

    /// Repairs the tower. Changes the health of the tower to full health and
    /// reduces player's money accordingly.
    void repair();

    /// Upgrade the tower into better one. Replaces current tower instance
    /// with new instance of the new tower class.
    void upgrade();

protected:
    int m_cost;
    int m_repair_cost;
    int m_upgrade_cost;
    //TODO: upgrade options as list of tower classes
};


#endif //TOWER_DEFENCE_2_TOWER_H
