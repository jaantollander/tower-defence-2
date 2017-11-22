#ifndef TOWER_DEFENCE_2_OBJECT_H
#define TOWER_DEFENCE_2_OBJECT_H


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
    Object(int x, int y, int radius, int speed, int health, int damage,
           int attack_range, int attack_speed);

    int x();
    int y();
    int radius();
    int health();

    void set_x(int x);
    void set_y(int y);

    /// Distance to another object.
    double distance(Object &other);

    /// Other objects that are within the attack range
    void within_attack_range(std::vector<Object*> &others);

    /// Change the speed of the object between zero and maximum speed.
    void change_speed(int amount);

    /// Object is regarded dead if it has health below of equal to zero.
    bool is_dead();

    /// Negative damages, positive heals, if reached zero, enemy dies, cannot go
    /// above max health
    void change_health(int amount);

    /// Deal damage to another object
    void deal_damage(Object &other);

protected:
    int m_x;
    int m_y;
    const int m_radius;
    int m_speed;
    const int m_max_speed;

    int m_health;
    const int m_max_health;
    const int m_damage;
    const int m_attack_range;
    const int m_attack_speed;
    TargetingPolicy m_targeting_policy;
};


#endif //TOWER_DEFENCE_2_OBJECT_H
