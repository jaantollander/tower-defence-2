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
    Tower(double x, double y, double radius, int damage, double attack_range,
          double attack_speed, TowerType *tower_type);
    ~Tower();

    TowerType *tower_type();

    Tower *upgrade(int index);

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

    std::string name() const;

    std::vector<TowerType *> upgrade_options();

    /// Add new upgrade option
    void add_upgrade_option(TowerType *tower_type);

    /// Create new tower of this type.
    Tower * create_tower(double x, double y);

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
