#include "tower.h"
#include "../map.h"

GameMap getMap() { return load_game_map("/maps/testmap1") }
//this is just for test!

TowerBase::TowerBase(int x, int y) : m_object(x, y, 0, 0) { }
TowerBase::~TowerBase() { }

TowerBase* TowerBase::upgrade() {
    if (m_upgradable) {
        GameMap m = getMap();   // Towers will need to know where
                                // they are for this to work!
                                // TODO
        m.get_tile(m_object.x(), m_object.y()) -> update_tower(m_upgrades_to);
        return m.get_tile(m_object.x(), m_object.y()) -> tower();
    }
}

