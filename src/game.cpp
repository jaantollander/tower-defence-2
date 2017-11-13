#include "game.h"


GameStats::GameStats(int time=0, int score=0, int money=0) :
        m_time(time), m_score(score), m_money(money) { }


Tile::Tile(bool is_walkable, bool is_buildable, TowerBase* tower= nullptr) :
        m_is_walkable(is_walkable), m_is_buildable(is_buildable),
        m_tower(tower){}


GameMap::GameMap(int xsize, int ysize) : m_xsize(xsize), m_ysize(ysize) {
    //TODO: initialize tiles

}


GameEngine::GameEngine(GameStats &stats,
                       GameMap &game_map,
                       Towers &towers,
                       Enemies &enemies) :
        m_stats(stats),
        m_game_map(game_map),
        m_towers(towers),
        m_enemies(enemies) {}
