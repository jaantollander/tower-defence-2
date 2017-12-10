#ifndef TOWER_DEFENCE_2_GRAPHICS_ENGINE_H
#define TOWER_DEFENCE_2_GRAPHICS_ENGINE_H

#include "graphicsButton.h"
#include <sstream>
#include "graphicsFunctions.h"
#include "../map/map.h"
#include "../engine.h"


class graphicsEngine{
public:
    explicit graphicsEngine(sf::RenderWindow &window);
    void addButtons();
    void addStatsWindow();

    void drawMenu();

    void drawTiles(GameMap map);
    void drawStats(GameEngine *game_engine);
    void drawGameBtns();

    void drawCreatures(std::vector<sf::Vector3f> creatures);
    void drawEnemies(Enemies enemies);

    void mouseBtnEventGame(GameEngine *game_engine);
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

    sf::Font m_font;
    std::vector<sf::Drawable *> m_statsTexts;


};


#endif