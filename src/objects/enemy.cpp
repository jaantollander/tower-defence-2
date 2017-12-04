#include "enemy.h"


Enemy::Enemy(double x, double y, double radius, double speed, int health,
             EnemyType *enemy_type) :
        Object(x, y, radius, speed, health, 0, 0, 0),
        m_enemy_type(enemy_type)
        {}

Enemy::~Enemy() {

}

int Enemy::score() const {
    return m_enemy_type->score();
}

int Enemy::money() const {
    return m_enemy_type->money();
}


EnemyType::EnemyType(const std::string &name, int score, int money,
                     double speed, int health) :
        m_name(name),
        m_score(score),
        m_money(money),
        m_speed(speed),
        m_health(health)
        {}


EnemyType::~EnemyType() {

}

Enemy EnemyType::create_enemy(double x, double y) {
    return Enemy(x, y, 1, m_speed, m_health, this);
}

int EnemyType::score() const {
    return m_score;
}

int EnemyType::money() const {
    return m_money;
}
