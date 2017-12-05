
graphicsEngine::graphicsEngine(sf::RenderWindow &window):
                                        m_window(window){

    m_mapSize = sf::Vector2f(600.f, 600.f);
    m_sideBarSize = sf::Vector2f(200.f, m_mapSize.y);
    m_windowSize = sf::Vector2f(m_mapSize.x + m_sideBarSize.x, m_mapSize.y);

    m_currentScreen = mainScreen;

    m_gameBtns = createAndDrawGame(m_window, m_mapSize, m_sideBarSize);
    m_window.clear();
    m_menuBtns = createAndDrawMenu(m_window, m_windowSize);
    m_window.clear();

}

void graphicsEngine::asd(){

}