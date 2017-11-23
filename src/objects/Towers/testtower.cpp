//
// Created by tero on 21.11.2017.

#include "testtower.h"
#include "test2.h"

TestTower::TestTower(int x, int y) : TowerBase(x, y) {
    m_name = "test1";
    m_cost = 100;
    m_upgrade_cost = 250;
    m_upgradable = true;
    m_upgrades_to = new Test2(x, y);
    m_object.change_radius(4);
    m_object.change_health(1);
    m_object.change_damage(10);
    m_object.change_attack_speed(5);
}


