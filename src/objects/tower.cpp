#include "tower.h"


Tower::Tower(int x, int y, int radius, int damage, int attack_range,
             int attack_speed, TowerType *tower_type) :
        Object(x, y, radius, 0, 0, damage, attack_range, attack_speed),
        m_tower_type(tower_type)
        {}

TowerType::TowerType(const std::string &name, int cost, int damage,
                     int attack_range, int attack_speed) :
        m_name(name),
        m_cost(cost),
        m_upgrade_options({}),
        m_damage(damage),
        m_attack_range(attack_range),
        m_attack_speed(attack_speed)
        {}

Tower::~Tower() {

}

TowerType *Tower::tower_type() {
    return m_tower_type;
}

Tower *Tower::upgrade(int index) {
    //TODO: check index out of bounds
    auto upgrade_options = m_tower_type->upgrade_options();
    auto new_tower_type = upgrade_options[index];
    //TODO: x and y types
    return new_tower_type->create_tower(this->x(), this->y());
}

TowerType::~TowerType() {

}

std::vector<TowerType *> TowerType::upgrade_options() {
    return m_upgrade_options;
}

void TowerType::add_upgrade_option(TowerType *tower_type) {
    m_upgrade_options.push_back(tower_type);
}

Tower * TowerType::create_tower(int x, int y) {
    return new Tower(x, y, 1, m_damage, m_attack_range, m_attack_speed, this);
}

std::string TowerType::name() const {
    return m_name;
}
