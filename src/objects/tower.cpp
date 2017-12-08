#include "tower.h"


Tower::Tower(double x, double y, double radius, int damage, double attack_range,
             double attack_speed, TowerType *tower_type) :
        Object(x, y, radius, 0, 0, damage, attack_range, attack_speed),
        m_tower_type(tower_type)
        {}

TowerType::TowerType(const std::string &name, int cost, int damage,
                     double attack_range, double attack_speed) :
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

std::vector<TowerType *> TowerType::upgrade_options() const {
    return m_upgrade_options;
}

void TowerType::add_upgrade_option(TowerType *tower_type) {
    m_upgrade_options.push_back(tower_type);
}

Tower * TowerType::create_tower(double x, double y) {
    return new Tower(x, y, 1, m_damage, m_attack_range, m_attack_speed, this);
}

std::string TowerType::name() const {
    return m_name;
}

const int TowerType::cost() const {
    return m_cost;
}

const int TowerType::damage() const {
    return m_damage;
}

const double TowerType::attack_range() const {
    return m_attack_range;
}

const double TowerType::attack_speed() const {
    return m_attack_speed;
}
