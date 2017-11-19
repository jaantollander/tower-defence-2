#ifndef TOWER_DEFENCE_2_COMBAT_H
#define TOWER_DEFENCE_2_COMBAT_H

#include <list>


/// Targeting policy dictates which enemy we should be attacking.
enum TargetingPolicy {
    target_first,
    target_last,
    target_least_health
};


/// Base class for implementing combat related features to objects.
class Combat {
public:
    Combat(int health, int damage, int attack_range, int attack_speed);

    /// Health
    int health();

    /// Object is regarded dead if it has health below of equal to zero.
    bool is_dead();

    /// Negative damages, positive heals, if reached zero, enemy dies, cannot go
    /// above max health
    void change_health(int amount);

    /// Deal damage to another object
    void deal_damage(Combat &other);

    /// Other combat objects that are withing the attack range
    void in_range(std::list<Combat*> &others);

protected:
    int m_health;
    const int m_max_health;
    const int m_damage;
    const int m_attack_range;
    const int m_attack_speed;
    TargetingPolicy m_targeting_policy;
};


#endif //TOWER_DEFENCE_2_COMBAT_H
