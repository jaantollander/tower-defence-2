#ifndef TOWER_DEFENCE_2_TOWER_H
#define TOWER_DEFENCE_2_TOWER_H

#include "combat.h"
#include "object.h"


/* Base class for all towers.
 */
class TowerBase : public Object, public Combat {
public:
    //TODO: constructor

    /* Repairs the tower. Changes the health of the tower to full health and
     * reduces player's money accordingly.
     */
    void repair();

    /* Upgrade the tower into better one.
     */
    void upgrade();

protected:
    int cost;
    int repair_cost;
    int upgrade_cost;

};

#endif //TOWER_DEFENCE_2_TOWER_H
