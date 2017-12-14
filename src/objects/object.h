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

/// Base class for objects in tower defence. Contains position, speed and the
/// movement of the object.
class Object {
public:
    Object(double x, double y, double radius, double speed, int health,
           int damage, double attack_range, double attack_speed);

    double x() const;
    double y() const;
    double radius() const;
    double speed() const;
    double distance_travelled() const;
    int health() const;
    int max_health() const;
    int damage() const;
    double attack_speed() const;
    double attack_range() const;
    TargetingPolicy targeting_policy() const;
    double time_since_last_attack() const;

    void position(double x, double y);

    /// Change the speed of the object between zero and maximum speed.
    void speed(double amount);

    /// Object is regarded dead if it has health below of equal to zero.
    bool is_dead();

    /// Negative damages, positive heals, if reached zero, enemy dies, cannot go
    /// above max health
    void health(int amount);

    /// Change damage
    void damage(int new_dmg);

    /// Change attack speed
    void attack_speed(int new_speed);

    /// Change target policy
    void change_policy(TargetingPolicy new_policy);

    /// Change distace travelled
    void distace_travelled(double d);

    /// Distance from other object
    double distance(Object &other);

    /// Attack to another object. Takes account the attack speed of the object.
    bool attack(Object &other, double timestep);

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
    /// Distance travelled by object
    double m_distance_travelled;
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
    /// Time since last time tower attacked. Used for attack speed.
    double m_time_since_last_attack;
};


#endif //TOWER_DEFENCE_2_OBJECT_H




