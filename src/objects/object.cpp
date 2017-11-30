#include <cmath>
#include <iostream>
#include "object.h"


Object::Object(int x, int y, int radius, int speed, int health, int damage,
               int attack_range, int attack_speed) :
        m_x(x), m_y(y),
        m_radius(radius),
        m_speed(speed), m_max_speed(speed),
        m_health(health), m_max_health(health),
        m_damage(damage),
        m_attack_speed(attack_speed),
        m_attack_range(attack_range),
        m_targeting_policy(target_last)
        { }


int Object::x() { return m_x; }
int Object::y() { return m_y; }
int Object::radius() { return m_radius; }
int Object::damage() { return m_damage; }
//void Object::set_x(int x) { m_xindex = x; }
//void Object::set_y(int y) { m_y = y; }


double Object::distance(Object &other) {
    return hypot((m_x - other.x()), (m_y - other.y())) - (m_radius + other.radius());
}

void Object::change_speed(int amount) {
    int new_speed = m_speed + amount;
    if (new_speed < 0)
        m_speed = 0;
    else if (new_speed > m_max_speed)
        m_speed = m_max_speed;
    else
        m_speed = new_speed;
}

void Object::change_radius(int new_r) { if (new_r > 0) m_radius = new_r; }
void Object::change_damage(int new_dmg) { m_damage = new_dmg; }
void Object::change_attack_speed(int new_speed) {
    if (new_speed > 0) m_attack_speed = new_speed;
}

int Object::health() { return m_health; }

bool Object::is_dead() { return m_health <= 0; }

void Object::change_health(int amount) {
    if (not this->is_dead()) {
        m_health += amount;
        if (m_health < 0)
            m_health = 0;
        else if (m_health > m_max_health)
            m_health = m_max_health;
    }
}

void Object::deal_damage(Object& other) {
    other.change_health(-m_damage);
}


