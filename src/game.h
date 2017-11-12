#ifndef TOWER_DEFENCE_2_GAME_H
#define TOWER_DEFENCE_2_GAME_H


/* Game class contains the game map, enemies, towers and game stats. This
 * class is also responsible for the implementation of the main game loop.
 */
class GameEngine {
public:
    //TODO: constructor

    /* Updates the game loop
     *
     * - movement of the enemies
     * - towers shoot
     * - enemies shoot
     * - update game stats
     */
    void update();

private:
    GameStats stats;
    GameMap game_map;
};


/* Class that contains information about the stats such as how much money
 * the player has and the score of the player.
 */
class GameStats {
public:
    GameStats(int time=0, int score=0, int money) : m_time(time),
                                                    m_score(score),
                                                    m_money(money) { }
    void update_time();
    void change_score();
    void change_money();

private:
    int m_time;
    int m_score;
    int m_money;
};


/* Individual tile in the game map.
 */
class Tile {
public:
    Tile() {}
    //TODO: attributes for what can be placed on this tile if anything
private:
    bool is_walkable;
    bool is_buildable;
};


/* The map of the game. Contains information about the path that enemies
 * follow and where towers can be placed.
 */
class GameMap {
public:
    //TODO: constructor
    //TODO: Grid, How should the tiling be implemented?

    /* Load game map from file.
     */
    void load_from_file();

private:
    int x_size;
    int y_size;
    //TODO: grid of tiles
    std::list<Enemy> enemies;
    std::list<Tower> towers;
};


#endif //TOWER_DEFENCE_2_GAME_H
