
graphicsEngine::graphicsEngine(sf::RenderWindow &window):
                                        m_window(window){

    m_mapSize = sf::Vector2f(600.f, 600.f);
    m_sideBarSize = sf::Vector2f(200.f, m_mapSize.y);
    m_windowSize = sf::Vector2f(m_mapSize.x + m_sideBarSize.x, m_mapSize.y);

    m_currentScreen = mainScreen;
    sf::Font m_font;
    m_font.loadFromFile("FreeMono.ttf");

    addButtons();

    //std::cout << m_statsTexts[2].getPosition().x << std::endl;
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

void graphicsEngine::addStatsWindow(){

    sf::RectangleShape statsArea(m_sideBarSize); // Stats
    statsArea.setPosition(m_mapSize.x, 0);
    statsArea.setFillColor(sf::Color(200,200,200));	// Light gray
    statsArea.setOutlineColor(sf::Color::White);
    statsArea.setOutlineThickness(5);
    m_window.draw(statsArea);

    sf::Font font;
    font.loadFromFile("FreeMono.ttf");

    sf::Text txt1("Points: ", font, 24);
    txt1.setColor(sf::Color::Black);
    txt1.setStyle(sf::Text::Bold);
    txt1.setPosition(sf::Vector2f(640, 50));
    m_window.draw(txt1);

    sf::Text txt2("Round: ", font, 24);
    txt2.setColor(sf::Color::Black);
    txt2.setStyle(sf::Text::Bold);
    txt2.setPosition(650, 150);
    m_window.draw(txt2);

    sf::Text txt3("Resources: ", font, 24);
    txt3.setColor(sf::Color::Black);
    txt3.setStyle(sf::Text::Bold);
    txt3.setPosition(620, 250);
    m_window.draw(txt3);
}

void graphicsEngine::drawStats(int score){

    sf::Font font;
    font.loadFromFile("FreeMono.ttf");

    std::stringstream ss;
    ss << score;

    sf::Text points(ss.str(), font, 22);
    points.setColor(sf::Color::Black);
    points.setPosition(sf::Vector2f(660, 80));
    m_window.draw(points);

    ss.str("");
    ss << 1;

    sf::Text round(ss.str(), font, 24);
    round.setColor(sf::Color::Black);
    round.setPosition(660, 180);
    m_window.draw(round);

    ss.str("");
    ss << 100;

    sf::Text resources(ss.str(), font, 24);
    resources.setColor(sf::Color::Black);
    resources.setPosition(660, 280);
    m_window.draw(resources);

    m_window.display();

}

void graphicsEngine::drawMenu(){

    sf::Font font;
    font.loadFromFile("FreeMono.ttf");

    for(int i=0; i < m_menuBtns.size(); i++){

        sf::RectangleShape tmp_btn(m_menuBtns[i].m_size);

        tmp_btn.setPosition(m_menuBtns[i].m_location);
        tmp_btn.setFillColor(sf::Color::Green);
        tmp_btn.setOutlineColor(sf::Color::White);
        tmp_btn.setOutlineThickness(5);

        sf::Text tmp_btnTxt(m_menuBtns[i].m_text, font, 34);

        tmp_btnTxt.setColor(sf::Color::White);
        tmp_btnTxt.setStyle(sf::Text::Bold);
        tmp_btnTxt.setPosition(m_menuBtns[i].m_location + sf::Vector2f(10,10));

        m_window.draw(tmp_btn);
        m_window.draw(tmp_btnTxt);
    }
    m_window.display();
}


void graphicsEngine::drawTiles(std::vector< std::vector<int> > map){

    int tileAmount = map[0].size();
    m_tileSize.x = m_mapSize.x / tileAmount;
    m_tileSize.y = m_mapSize.y / tileAmount;

    for (int i = 0; i < tileAmount; ++i) {
        for (int j = 0; j < tileAmount; ++j) {
            sf::RectangleShape tmpTile(m_tileSize);
            tmpTile.setPosition(j*m_tileSize.x, i*m_tileSize.y); // OBS j,i !
            tmpTile.setOutlineColor(sf::Color::White);
            tmpTile.setOutlineThickness(2);

            switch(map[i][j])
            {
                case 0: tmpTile.setFillColor(sf::Color::Green);
                    break;
                case 1: tmpTile.setFillColor(sf::Color::White);
                    break;
                case 2: tmpTile.setFillColor(sf::Color::Red);
                    break;
            }
            m_window.draw(tmpTile);
        }
    }
}


void graphicsEngine::drawCreatures(std::vector<sf::Vector3f> creatures){

    for (int i = 0; i < creatures.size(); ++i) {
        sf::CircleShape tmpCreature(std::min(m_tileSize.x, m_tileSize.y) / 2);
        tmpCreature.setPosition(creatures[i].x, creatures[i].y); // OBS j,i !

        switch((int) creatures[i].z) {
            case 1:
                tmpCreature.setFillColor(sf::Color::Blue);
                break;
            case 2:
                tmpCreature.setFillColor(sf::Color::Yellow);
                break;
        }

        m_window.draw(tmpCreature);
    }
}