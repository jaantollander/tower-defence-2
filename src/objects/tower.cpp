#include "tower.h"


Tower::Tower(int x, int y, int radius, int damage, int attack_range,
             int attack_speed, TowerType *tower_type) :
        Object(x, y, radius, 0, 0, damage, attack_range, attack_speed),
        m_tower_type(tower_type) {}


TowerType::TowerType(const std::string &name, int cost, int damage,
                     int attack_range,
                     int attack_speed) :
        m_name(name), m_cost(cost), m_upgrade_options({}), m_damage(damage),
        m_attack_range(attack_range), m_attack_speed(attack_speed) {}


TowerType::~TowerType() {

}

void TowerType::add_upgrade_option(TowerType *tower_type) {
    m_upgrade_options.push_back(tower_type);
}


Tower * TowerType::create_tower(int x, int y) {
    return new Tower(x, y, 1, m_damage, m_attack_range, m_attack_speed, this);
}


//TODO: the actual swapping of new tower should happen in map class
//needs information about the map, for example:
//    map.get_tile(m_object.x(), m_object.y()) -> update_tower(m_upgrades_to);
//    return map.get_tile(m_object.x(), m_object.y()) -> tower();

Tower * TowerType::upgrade(int index, int x, int y) {
    //TODO: check that index not out of bound, exception message
    auto new_tower_type = m_upgrade_options[index];
    return new_tower_type->create_tower(x, y);
}
