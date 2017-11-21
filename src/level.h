#ifndef TOWER_DEFENCE_2_LEVEL_H
#define TOWER_DEFENCE_2_LEVEL_H

#include <vector>
#include <string>
#include "objects/tower.h"


/// Contains information to start and run different game levels.
class GameLevel {
public:
    GameLevel(int initial_money, int enemies_spawned,
              std::vector<int> &enemy_spawn_interval);

    void increment_enemies_spawned();

private:
    const int m_initial_money;
    int m_enemies_spawned;
    const std::vector<int> m_enemy_spawn_interval;
};



#endif //TOWER_DEFENCE_2_LEVEL_H
