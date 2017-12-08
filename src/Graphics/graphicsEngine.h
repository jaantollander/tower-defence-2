#include "graphicsButton.h"
//#include "graphicsEngine.cpp"

class graphicsEngine{
public:
    
    graphicsEngine(sf::RenderWindow &window);
    void addButtons();
    void addStatsWindow();

    void drawMenu();

    void drawTiles(std::vector< std::vector<int> > map);
    void drawStats(int score);
    void drawGameBtns();
    void drawCreatures(std::vector<sf::Vector3f> creatures);

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
