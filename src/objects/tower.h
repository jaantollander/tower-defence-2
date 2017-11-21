#ifndef TOWER_DEFENCE_2_TOWER_H
#define TOWER_DEFENCE_2_TOWER_H

#include "combat.h"
#include "object.h"
#include <string>

/// Base class for all towers.
class TowerBase {
public:
    TowerBase(int x, int y);
    virtual ~TowerBase();

    /// Repairs the tower. Changes the health of the tower to full health and
    /// reduces player's money accordingly.
    /// Return the cost of the repair.
    ///int repair(); This might not be included?

    /// Upgrade the tower. Returns a pointer to the new tower instance.
    TowerBase* upgrade();

protected:
    std::string m_name;
    Object m_object;
    int m_damage;
    int m_attack_speed;
    int m_cost;
    int m_upgrade_cost;
    bool m_upgradable;
    TowerBase* m_upgrades_to;
    //TODO: upgrade options as container of tower classes, maybe enum?
};


#endif //TOWER_DEFENCE_2_TOWER_H
