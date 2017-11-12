#ifndef TOWER_DEFENCE_2_COMBAT_H
#define TOWER_DEFENCE_2_COMBAT_H


/* Targeting policy dictates which enemy we should be attacking.
 */
enum TargetingPolicy {
    first = 0,
    last = 1,
    least_health = 2
};


/* Base class for implementing combat related features to objects.
 */
class Combat {
public:
    //TODO: Constructor

    int getHealth() { return health; }

    /* Object is regarded dead if it has health below of equal to zero.
     */
    bool is_dead() { return health <= 0; };

    /* Negative damages, positive heals, if reached zero, enemy dies, cannot go
     * above max health
     */
    void change_health(int amount);

    /* Deal damage to another object
     */
    void deal_damage(Combat &other);

    /* Other combat objects that are withing the attack range
     */
    void in_range(std::list<Combat> &others);

protected:
    int health;
    int damage;
    int attack_range;
    int attack_speed;
    int max_health;
    TargetingPolicy targeting_policy;
};


#endif //TOWER_DEFENCE_2_COMBAT_H
