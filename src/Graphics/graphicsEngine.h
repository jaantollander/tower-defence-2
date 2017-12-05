#include "graphicsButton.h"

class graphicsEngine{
public:
    
    graphicsEngine(sf::RenderWindow &window);
    void addButtons();
    void addStats();
    void drawStats(int score);

    
//private:
    sf::Vector2f m_mapSize;
    sf::Vector2f m_sideBarSize;
    sf::Vector2f m_windowSize;

    sf::RenderWindow &m_window;
    Screens m_currentScreen;

    std::vector<graphicsButton> m_menuBtns;
    std::vector<graphicsButton> m_gameBtns;

    sf::Font m_font;
    std::vector<sf::Text> m_statsTexts;


};
