#include "tower.h"

Tower::Tower(int x, int y) :
        m_object(x, y, 0, 0, 0, 0, 0, 0) { }

Tower::~Tower() { }

Tower* Tower::upgrade(int index) {
    if (not m_upgrade_options.empty()) {
        // TODO
        // needs information about the map, for example:
        //map.get_tile(m_object.x(), m_object.y()) -> update_tower(m_upgrades_to);
        //return map.get_tile(m_object.x(), m_object.y()) -> tower();
    }
}

