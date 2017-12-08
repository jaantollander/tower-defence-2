#ifndef TOWER_DEFENCE_2_GRAPHICS_ENGINE_H
#define TOWER_DEFENCE_2_GRAPHICS_ENGINE_H

#include "graphicsButton.h"
#include <sstream>
#include "graphicsFunctions.h"

class graphicsEngine{
public:
    
    graphicsEngine(sf::RenderWindow &window);
    void addButtons();
    void addStatsWindow();

    void drawMenu();
    void drawStats(int score);

    void drawTiles(std::vector< std::vector<int> > map);
    void drawCreatures(std::vector<sf::Vector3f> creatures);
    
//private:
    sf::Vector2f m_mapSize;
    sf::Vector2f m_sideBarSize;
    sf::Vector2f m_windowSize;
    sf::Vector2f m_tileSize;

    sf::RenderWindow &m_window;
    Screens m_currentScreen;

    std::vector<graphicsButton> m_menuBtns;
    std::vector<graphicsButton> m_gameBtns;

    sf::Font m_font;
    std::vector<sf::Drawable *> m_statsTexts;


};


#endif