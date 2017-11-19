#ifndef TOWER_DEFENCE_2_STATS_H
#define TOWER_DEFENCE_2_STATS_H

/// Class that contains information about the stats such as how much money
/// the player has and the score of the player.
class GameStats {
public:
    GameStats(int time, int score, int money);

    /// Increments the game time by 1.
    void update_time();

    /// Change player's score. Game score can't go below zero.
    void change_score(int amount);

    /// Change player's money. Return false and doesn't change the value if the
    /// amount of change would drop player's money below zero otherwise returns
    /// true and changes the money based on the amount given.
    bool change_money(int amount);

private:
    int m_time;
    int m_score;
    int m_money;
};

#endif //TOWER_DEFENCE_2_STATS_H
