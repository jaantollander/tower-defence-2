#include "tower.h"

TowerBase::TowerBase(int x, int y) : m_object(x, y, 0, 0, 0, 0, 0) { }
TowerBase::~TowerBase() { }

TowerBase* TowerBase::upgrade() {
    if (m_upgradable) {
        // TODO
        // needs information about the map, for example:
        //map.get_tile(m_object.x(), m_object.y()) -> update_tower(m_upgrades_to);
        //return map.get_tile(m_object.x(), m_object.y()) -> tower();
    }
}

