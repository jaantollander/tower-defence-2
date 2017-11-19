#include "combat.h"


Combat::Combat(int health, int damage, int attack_range, int attack_speed) :
        m_health(health), m_max_health(health), m_damage(damage),
        m_attack_range(attack_range), m_attack_speed(attack_speed),
        m_targeting_policy(target_last) {}


int Combat::health() { return m_health; }
bool Combat::is_dead() { return m_health <= 0; }


void Combat::change_health(int amount) {
    if (not this->is_dead()) {
        m_health += amount;
        if (m_health < 0)
            m_health = 0;
        else if (m_health > m_max_health)
            m_health = m_max_health;
    }
};
