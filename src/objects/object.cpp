#include <cmath>
#include "object.h"


Object::Object(double x, double y, double radius, double speed, int health,
               int damage, double attack_range, double attack_speed) :
        m_x(x), m_y(y),
        m_radius(radius),
        m_speed(speed), m_max_speed(speed),
        m_distance_travelled(0.0),
        m_health(health), m_max_health(health),
        m_damage(damage),
        m_attack_speed(attack_speed),
        m_attack_range(attack_range),
        m_targeting_policy(target_first),
        m_time_since_last_attack(attack_speed)
        { }

double Object::x() const {
    return m_x;
}

double Object::y() const {
    return m_y;
}

double Object::radius() const {
    return m_radius;
}

double Object::speed() const {
    return m_speed;
}

double Object::distance_travelled() const {
    return m_distance_travelled;
}

int Object::health() const {
    return m_health;
}

int Object::damage() const {
    return m_damage;
}

double Object::attack_speed() const {
    return m_attack_speed;
}

double Object::attack_range() const {
    return m_attack_range;
}

TargetingPolicy Object::targeting_policy() const {
    return m_targeting_policy;
}

double Object::time_since_last_attack() const {
    return m_time_since_last_attack;
}

void Object::position(double x, double y) {
    m_x = x;
    m_y = y;
}

bool Object::is_dead() {
    return m_health <= 0;
}

void Object::health(int amount) {
    if (not this->is_dead()) {
        m_health += amount;
        if (m_health < 0)
            m_health = 0;
        else if (m_health > m_max_health)
            m_health = m_max_health;
    }
}

void Object::speed(double amount) {
    auto new_speed = m_speed + amount;
    if (new_speed < 0)
        m_speed = 0;
    else if (new_speed > m_max_speed)
        m_speed = m_max_speed;
    else
        m_speed = new_speed;
}

void Object::damage(int new_dmg) {
    m_damage = new_dmg;
}

void Object::attack_speed(int new_speed) {
    if (new_speed > 0)
        m_attack_speed = new_speed;
}

void Object::distace_travelled(double d) {
    m_distance_travelled += d;
}

double Object::distance(Object &other) {
    return hypot((m_x - other.x()), (m_y - other.y()));
}

bool Object::attack(Object &other, double timestep) {
    if (m_time_since_last_attack >= m_attack_speed) {
        other.health(-m_damage);
        m_time_since_last_attack = 0.0;
        return true;
    }
    m_time_since_last_attack += timestep;
    return false;
}
