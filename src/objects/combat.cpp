#include "combat.h"


void Combat::change_health(int amount) {
    if (not this->is_dead()) {
        health += amount;
        if (health < 0)
            health = 0;
        else if (health > max_health)
            health = max_health;
    }
};
