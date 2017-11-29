#ifndef TOWER_DEFENCE_2_OBJECT_H
#define TOWER_DEFENCE_2_OBJECT_H

#include <vector>


//TODO: target multiple enemies (AOE)


/// Targeting policy dictates which enemy we should be attacking.
enum TargetingPolicy {
    target_first,
    target_last,
    target_least_health
};


// TODO: types int/double?

/// Base class for objects in tower defence. Contains position, speed and the
/// movement of the object.
class Object {
public:
    Object(int x, int y, int radius, int speed, int health, int damage,
           int attack_range, int attack_speed);

    int x();
    int y();
    int radius();
    int health();

    /// Change the speed of the object between zero and maximum speed.
    void change_speed(int amount);

    /// Object is regarded dead if it has health below of equal to zero.
    bool is_dead();

    /// Negative damages, positive heals, if reached zero, enemy dies, cannot go
    /// above max health
    void change_health(int amount);

    /// Changes radius, damage or attack speed
    void change_radius(int new_r);
    void change_damage(int new_dmg);
    void change_attack_speed(int new_speed);

    /// Deal damage to another object
    void deal_damage(Object &other);

    /// Distance from other object
    double distance(Object &other);

    /// Other combat objects that are withing the attack range
    void within_attack_range(std::vector<Object *> &others);
    std::vector<Object *> enemies_in_range();

protected:
    /// x coordinate of the object
    int m_x;
    /// u coordinate of the object
    int m_y;
    /// Radius of the object.
    int m_radius;
    /// Current speed of the object
    int m_speed;
    /// Maximum speed of the object
    const int m_max_speed;

    /// Current health of the object
    int m_health;
    /// Maximum health of the object
    const int m_max_health;
    /// Amount of damage each hit deals
    int m_damage;
    /// Attack speed, how fast does the object deal damage
    int m_attack_speed;
    /// Attack range, how far can the object deal damage
    int m_attack_range;
    /// Targeting policy, how will the object choose its target
    TargetingPolicy m_targeting_policy;
};


#endif //TOWER_DEFENCE_2_OBJECT_H




