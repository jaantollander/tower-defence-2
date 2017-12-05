
class graphicsEngine{
public:
    
    graphicsEngine(sf::RenderWindow &window);
    void asd();
    
//private:
    sf::Vector2f m_mapSize;
    sf::Vector2f m_sideBarSize;
    sf::Vector2f m_windowSize;

    sf::RenderWindow &m_window;
    Screens m_currentScreen;

    std::vector<sf::Vector2f> m_menuBtns;
    std::vector<sf::Vector2f> m_gameBtns;


};
