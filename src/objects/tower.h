#ifndef TOWER_DEFENCE_2_TOWER_H
#define TOWER_DEFENCE_2_TOWER_H

#include "object.h"
#include <vector>
#include <string>


//TODO: TowerType


/// Base class for all towers.
class Tower {
public:
    Tower(int x, int y);

    ~Tower();

    /// Upgrade the tower. Returns a pointer to the new tower instance.
    /// @param index is integer which denotes the index of the upgrade option
    ///        that was chosen.
    Tower* upgrade(int index);

protected:
    /// ???
    Object m_object;

    /// Name of the tower type
    std::string m_name;

    /// Cost to buy/upgrade for this tower type
    int m_cost;

    /// Pointer to the types of towers that this tower type can be upgraded to.
    /// If collection is empty tower type cannot be upgraded.
    std::vector<Tower *> m_upgrade_options;
};


#endif //TOWER_DEFENCE_2_TOWER_H
