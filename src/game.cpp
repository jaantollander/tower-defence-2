#include "game.h"


GameStats::GameStats(int time=0, int score=0, int money=0) :
        m_time(time), m_score(score), m_money(money) { }


Tile::Tile(bool is_buildable, bool is_path, Directions direction) :
        m_is_path(is_path), m_is_buildable(is_buildable),
        m_direction(direction) { }


GameMap::GameMap(int xsize, int ysize) : m_xsize(xsize), m_ysize(ysize) {
    // https://stackoverflow.com/questions/28663299/initializing-a-2d-vector
    Tiles tiles(ysize, std::vector<Tile*>(xsize, nullptr));
    for (int i = 0; i < ysize; ++i) {
        for (int j = 0; j < xsize; ++j) {
            Tile tile = Tile(false, false, undefined_direction);
            tiles[i][j] = &tile;
        }
    }
    m_tiles = tiles;
}


GameLevel::GameLevel(int starting_money) : m_starting_money(starting_money) {}


GameEngine::GameEngine(GameStats &stats, GameMap &game_map, GameLevel game_level,
                       Towers &towers, Enemies &enemies) :
        m_stats(stats),
        m_game_map(game_map),
        m_game_level(game_level),
        m_towers(towers),
        m_enemies(enemies) {}


void GameEngine::update() {
    //TODO: spawn new enemies according to level description
//    movement();
//    towers_attack();
//    enemies_attack();
//    m_stats.update_time();
}
