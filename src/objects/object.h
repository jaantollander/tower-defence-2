#ifndef TOWER_DEFENCE_2_OBJECT_H
#define TOWER_DEFENCE_2_OBJECT_H

#include <vector>

/// Targeting policy dictates which enemy we should be attacking.
enum TargetingPolicy {
    target_first,
    target_last,
    target_least_health
};


#include <vector>


/// Targeting policy dictates which enemy we should be attacking.
enum TargetingPolicy {
    target_first,
    target_last,
    target_least_health
};


/// Base class for objects in tower defence. Contains position, speed and the
/// movement of the object.
class Object {
public:
    Object(int x, int y, int radius, int speed, int health,
           int damage, int attack_speed);

    int x();
    int y();
    /// Change the speed of the object between zero and maximum speed.
    void change_speed(int amount);

    /// Health
    int health();

    /// Object is regarded dead if it has health below of equal to zero.
    bool is_dead();

    /// Negative damages, positive heals, if reached zero, enemy dies, cannot go
    /// above max health
    void change_health(int amount);

    /// Deal damage to another object
    void deal_damage(Object &other);

    /// Other combat objects that are withing the attack range
    void in_range(std::vector<Object*> &others);

    /// Health
    int health();

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

    /// Other combat objects that are withing the attack range
    void in_range(std::vector<Object*> &others);

protected:
    int m_x;
    int m_y;
    int m_radius;
    int m_speed;
    const int m_max_speed;

    int m_health;
    const int m_max_health;
    int m_damage;
    int m_attack_speed;
    TargetingPolicy m_targeting_policy;
    //int m_attack_range; Tämä turha jos radius on jo?
};


#endif //TOWER_DEFENCE_2_OBJECT_H




