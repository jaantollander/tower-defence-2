#ifndef TOWER_DEFENCE_2_TOWER_H
#define TOWER_DEFENCE_2_TOWER_H

#include "object.h"
#include <vector>
#include <string>


// Deferred declaration
class TowerType;


/// Tower class
class Tower : public Object {
public:
    Tower(int x, int y, int radius, int damage, int attack_range,
              int attack_speed, TowerType *tower_type);
    ~Tower();

    TowerType tower_type();

private:
    TowerType *m_tower_type;
};


/// Description for creating new towers
class TowerType {
public:
    TowerType(const std::string &name, int cost, int damage, int attack_range,
              int attack_speed);

    /// Destroy the object
    ~TowerType();

    /// Add new upgrade option
    void add_upgrade_option(TowerType *tower_type);

    /// Create new tower of this type.
    Tower * create_tower(int x, int y);

    /// Upgrade new tower if the player has enough money to upgrade.
    /// @param index is integer which denotes the index of the upgrade option
    ///        that was chosen.
    /// @returns a pointer to the new tower instance.
    Tower * upgrade(int index, int x, int y);

private:
    /// Name of the tower type
    const std::string m_name;

    /// Cost to buy/upgrade for this tower type
    const int m_cost;

    /// Pointer to the types of towers that this tower type can be upgraded to.
    /// If collection is empty tower type cannot be upgraded.
    std::vector<TowerType *> m_upgrade_options;

    // Initial values for new towers
    const int m_damage;
    const int m_attack_range;
    const int m_attack_speed;
};


#endif //TOWER_DEFENCE_2_TOWER_H
