
graphicsEngine::graphicsEngine(sf::RenderWindow &window):
                                        m_window(window){

    m_mapSize = sf::Vector2f(600.f, 600.f);
    m_sideBarSize = sf::Vector2f(200.f, m_mapSize.y);
    m_windowSize = sf::Vector2f(m_mapSize.x + m_sideBarSize.x, m_mapSize.y);

    m_currentScreen = mainScreen;
    sf::Font m_font;
    m_font.loadFromFile("FreeMono.ttf");

    addButtons();
    addStats();

    std::cout << m_statsTexts[0].getPosition().x
              << std::endl;
}

void graphicsEngine::addButtons(){
    m_menuBtns.push_back(graphicsButton(
            sf::Vector2f(100, 200),
            sf::Vector2f(160, 120),
            std::string("Start")
    ));
    m_menuBtns.push_back(graphicsButton(
            sf::Vector2f(330, 100),
            sf::Vector2f(100, 100),
            std::string("Map\n 1")
    ));
    m_menuBtns.push_back(graphicsButton(
            sf::Vector2f(330, 230),
            sf::Vector2f(100, 100),
            std::string("Map\n 2")
    ));


    m_gameBtns.push_back(graphicsButton(
            sf::Vector2f(600, 500),
            sf::Vector2f(200, 100),
            std::string("Main Menu")
    ));
}

void graphicsEngine::addStats(){
    m_statsTexts.push_back(sf::Text("Points: ", m_font, 24));
    m_statsTexts[0].setColor(sf::Color::Black);
    m_statsTexts[0].setStyle(sf::Text::Bold);
    m_statsTexts[0].setPosition(sf::Vector2f(640, 50));

    m_statsTexts.push_back(sf::Text("Round: ", m_font, 24));
    m_statsTexts[1].setColor(sf::Color::Black);
    m_statsTexts[1].setStyle(sf::Text::Bold);
    m_statsTexts[1].setPosition(650, 150);

    m_statsTexts.push_back(sf::Text("Resources: ", m_font, 24));
    m_statsTexts[2].setColor(sf::Color::Black);
    m_statsTexts[2].setStyle(sf::Text::Bold);
    m_statsTexts[2].setPosition(620, 250);
}

void graphicsEngine::drawStats(int score){
    std::vector<sf::Drawable *> drawables;

    std::stringstream ss;
    ss << score;

    sf::Text points(ss.str(), m_font, 22);
    points.setColor(sf::Color::Black);
    points.setPosition(sf::Vector2f(660, 80));
    drawables.push_back(&points);

    ss.str("");
    ss << 1;

    sf::Text round(ss.str(), m_font, 24);
    round.setColor(sf::Color::Black);
    round.setPosition(660, 180);
    drawables.push_back(&round);

    ss.str("");
    ss << 100;

    sf::Text resources(ss.str(), m_font, 24);
    resources.setColor(sf::Color::Black);
    resources.setPosition(660, 280);
    drawables.push_back(&resources);

    drawDrawables(m_window, drawables);
}
