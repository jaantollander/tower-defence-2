#ifndef TOWER_DEFENCE_2_GRAPHICS_ENGINE_H
#define TOWER_DEFENCE_2_GRAPHICS_ENGINE_H

#include "graphicsButton.h"
#include <sstream>
#include <queue>
#include "graphicsFunctions.h"
#include "../map/map.h"
#include "../engine.h"

class GameEngine;

class graphicsEngine{
public:
    explicit graphicsEngine(sf::RenderWindow &window);

    friend class GameEngine;

    void addButtons();
    void drawMenu();

    void addStatsWindow();
    void drawStats(GameEngine *game_engine);
    void drawEventBox();
    void addEvent(std::string str);
    void drawGameBtns();

    void drawTiles(GameMap map);
    void drawEnemies(Enemies enemies);

    void drawAttack(Tower tower, Enemy enemy);

    void mouseBtnEventGame(GameEngine *game_engine);
    void endMessage(bool win, bool done);
    int pollMainScreen();
    sf::Vector3f pollGameScreen();
    
//private:
    sf::Vector2f m_mapSize;
    sf::Vector2f m_sideBarSize;
    sf::Vector2f m_windowSize;
    sf::Vector2f m_tileSize;

    bool m_buildFlag;
    bool m_upgFlag;

    sf::RenderWindow &m_window;
    Screens m_currentScreen;

    std::vector<graphicsButton> m_menuBtns;
    std::vector<graphicsButton> m_gameBtns;

    std::deque<std::string> m_gameEvents;


    sf::Font m_font;
    std::vector<sf::Drawable *> m_statsTexts;
};


#endif