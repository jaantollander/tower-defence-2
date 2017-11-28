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


class Object;
typedef std::vector<Object *> Objects;


/// Base class for objects in tower defence. Contains position, speed and the
/// movement of the object.
class Object {
public:
    Object(double x, double y, double radius, double speed, int health,
           int damage, double attack_range, double attack_speed);

    double x();
    double y();
    double radius();
    int health();

    /// Change the speed of the object between zero and maximum speed.
    void change_speed(double amount);

    /// Object is regarded dead if it has health below of equal to zero.
    bool is_dead();

    /// Negative damages, positive heals, if reached zero, enemy dies, cannot go
    /// above max health
    void change_health(int amount);

    /// Change damage
    void change_damage(int new_dmg);

    /// Change attack speed
    void change_attack_speed(int new_speed);

    /// Distance from other object
    double distance(Object &other);

    /// Other combat objects that this object can target.
    /// - withing the attack range
    /// - targeting policy
    Objects find_targets(Objects &others);

    /// Deal damage to another object
    void deal_damage(Object &other);

protected:
    /// x coordinate of the object
    double m_x;
    /// u coordinate of the object
    double m_y;
    /// Physical radius of the object.
    const double m_radius;
    /// Current speed of the object
    double m_speed;
    /// Maximum speed of the object
    const double m_max_speed;

    /// Current health of the object
    int m_health;
    /// Maximum health of the object
    const int m_max_health;
    /// Amount of damage each hit deals
    int m_damage;
    /// Attack speed, how fast does the object deal damage
    double m_attack_speed;
    /// Attack range, how far can the object deal damage
    double m_attack_range;
    /// Targeting policy, how will the object choose its target
    TargetingPolicy m_targeting_policy;
};


#endif //TOWER_DEFENCE_2_OBJECT_H




