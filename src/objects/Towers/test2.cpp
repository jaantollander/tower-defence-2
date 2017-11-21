//
// Created by tero on 21.11.2017.
//

#include "test2.h"

Test2::Test2(int x, int y) : TowerBase(x, y) {
    m_name = "test2";
    m_cost = 300;
    m_upgrade_cost = 0;
    m_upgradable = false;
    m_upgrades_to = nullptr;
    m_object.change_radius(4);
    m_object.change_health(1);
    m_object.change_damage(20);
    m_object.change_attack_speed(8);
}