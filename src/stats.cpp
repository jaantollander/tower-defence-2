#include "engine.h"

GameStats::GameStats(int time, int score, int money) :
        m_time(time), m_score(score), m_money(money) { }

void GameStats::update_time() { m_time++; }

void GameStats::change_score(int amount) {
    int new_score = m_score + amount;
    if (new_score < 0)
        m_score = 0;
    else
        m_score = new_score;
}

bool GameStats::change_money(int amount) {
    int new_money = m_money + amount;
    if (new_money < 0)
        return false;
    else {
        m_money = new_money;
        return true;
    }
}
