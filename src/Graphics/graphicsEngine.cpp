#include "graphicsEngine.h"
#include "../map/map.h"


graphicsEngine::graphicsEngine(sf::RenderWindow &window):
        m_window(window){
    m_mapSize = sf::Vector2f(600.f, 600.f);
    m_sideBarSize = sf::Vector2f(200.f, m_mapSize.y);
    m_windowSize = sf::Vector2f(m_mapSize.x + m_sideBarSize.x, m_mapSize.y);

    m_buildFlag = false;
    m_upgFlag = false;

    m_currentScreen = mainScreen;

    sf::Font m_font;
    m_font.loadFromFile("../src/Graphics/FreeMono.ttf");

    addButtons();
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
            std::string(" Main\n  Menu")
    ));

    m_gameBtns.push_back(graphicsButton(
            sf::Vector2f(600, 400),
            sf::Vector2f(100, 100),
            std::string("Buy")
    ));

    m_gameBtns.push_back(graphicsButton(
            sf::Vector2f(700, 400),
            sf::Vector2f(100, 100),
            std::string("Up-\ngrd")
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
    font.loadFromFile("../src/Graphics/FreeMono.ttf");

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
    font.loadFromFile("../src/Graphics/FreeMono.ttf");

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

}

void graphicsEngine::drawMenu(){

    sf::Font font;
    font.loadFromFile("../src/Graphics/FreeMono.ttf");

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

void graphicsEngine::drawTiles(GameMap map){

    int tileAmount_x = map.tiles().xsize;
    int tileAmount_y = map.tiles().ysize;

    m_tileSize.x = m_mapSize.x / tileAmount_x;
    m_tileSize.y = m_mapSize.y / tileAmount_y;

    for (int i = 0; i < tileAmount_x; ++i) {
        for (int j = 0; j < tileAmount_y; ++j) {

            sf::RectangleShape tmpTile(m_tileSize);
            tmpTile.setPosition(i*m_tileSize.x, j*m_tileSize.y);
            tmpTile.setOutlineColor(sf::Color::White);
            tmpTile.setOutlineThickness(2);

            switch(map.tiles().tile(i,j)->tile_type())
            {
                case path: tmpTile.setFillColor(sf::Color::White);
                    break;
                case grass: tmpTile.setFillColor(sf::Color::Green);
                    break;
                case water: tmpTile.setFillColor(sf::Color::Blue);
                    break;
                case undefined_tile_type: tmpTile.setFillColor(sf::Color::Black);
                    break;
            }
            m_window.draw(tmpTile);

            if( map.tiles().tile(i,j)->tower()->damage() > 0 ){
                sf::CircleShape tmpTower(std::min(m_tileSize.x,
                                                  m_tileSize.y) / 2.5, 3);
                tmpTower.setPosition(sf::Vector2f((i+0.12) * m_tileSize.x,
                                                  (j+0.12) * m_tileSize.y));

                switch(map.tiles().tile(i,j)->upgrade_level()){
                    case 1: tmpTower.setFillColor(sf::Color(200,200,200));
                        break;
                    case 2: tmpTower.setFillColor(sf::Color::Cyan);
                        break;
                    case 3: tmpTower.setFillColor(sf::Color::Magenta);
                        break;
                    default:tmpTower.setFillColor(sf::Color::White);
                        break;
                }

                m_window.draw(tmpTower);
            }

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

void graphicsEngine::drawEnemies(Enemies enemies){

    //std::cout << enemies.size() << std::endl;

    for (int i = 0; i < enemies.size(); ++i) {
        sf::CircleShape tmpEnemy(std::min(m_tileSize.x, m_tileSize.y) / 2);
        tmpEnemy.setPosition(enemies[i]->x() * m_tileSize.x,
                             enemies[i]->y() * m_tileSize.y);
        tmpEnemy.setFillColor(sf::Color::Red);

        m_window.draw(tmpEnemy);
    }
}


void graphicsEngine::mouseBtnEventHandler(GameEngine *game_engine){

    sf::Vector3f gameBtnPressed = pollGameScreen();

    switch( (int) gameBtnPressed.z ){
        case 0: {
            m_window.clear();
            m_currentScreen = mainScreen;
            drawMenu();
            break;
        }
        case -1: {
            std::cout << "Select a place to build" << std::endl;
            m_buildFlag = true;
            break;
        }
        case -2: {
            std::cout << "Select the tower to upgrade" << std::endl;
            m_upgFlag = true;
            break;
        }
        case -3: {
            break;
        }
        default: {
            if( m_buildFlag ){
                game_engine->upgrade_tower(gameBtnPressed.x, gameBtnPressed.y, 0);
                std::cout << "Built tower at " <<
                          gameBtnPressed.x << " ; " <<
                          gameBtnPressed.y << std::endl;
                m_buildFlag = false;
            }else if( m_upgFlag ){
                game_engine->upgrade_tower(gameBtnPressed.x, gameBtnPressed.y, 1);
                std::cout << "Upgraded tower at " <<
                          gameBtnPressed.x << " ; " <<
                          gameBtnPressed.y << std::endl;
                m_upgFlag = false;
            }
            break;
        }
    }
}

int graphicsEngine::pollMainScreen(){
    int btnPressed = 1;

    int mPosx = sf::Mouse::getPosition(m_window).x;
    int mPosy = sf::Mouse::getPosition(m_window).y;

    if(mPosy > 0 && mPosx < m_windowSize.x)
    {
        int idx = 0;
        for(; idx < m_menuBtns.size(); idx++){
            if( mPosx >= m_menuBtns[idx].m_location.x &&
                mPosy >= m_menuBtns[idx].m_location.y &&
                mPosx <= m_menuBtns[idx].m_location.x + m_menuBtns[idx].m_size.x &&
                mPosy <= m_menuBtns[idx].m_location.y + m_menuBtns[idx].m_size.y){
                break;
            }
        }
        btnPressed = -1*idx;
    }

    return btnPressed;
}

sf::Vector3f graphicsEngine::pollGameScreen(){

    sf::Vector3f btnPressed(100.f,100.f, 1.f);

    int mPosx = sf::Mouse::getPosition(m_window).x;
    int mPosy = sf::Mouse::getPosition(m_window).y;

    if( mPosy > 0 && mPosx < m_mapSize.x )
    {
        btnPressed.x = floor(mPosx / m_tileSize.x);
        btnPressed.y = floor(mPosy / m_tileSize.y);
    }
    else if(mPosy > 0 && mPosx < m_windowSize.x)
    {
        int idx = 0;
        for(; idx < m_gameBtns.size(); idx++){
            if( mPosx >= m_gameBtns[idx].m_location.x &&
                mPosy >= m_gameBtns[idx].m_location.y &&
                mPosx <= m_gameBtns[idx].m_location.x + m_gameBtns[idx].m_size.x &&
                mPosy <= m_gameBtns[idx].m_location.y + m_gameBtns[idx].m_size.y){
                break;
            }
        }
        btnPressed.z = -1*idx;
        m_buildFlag = false;
        m_upgFlag = false;
    }

    return btnPressed;
}

void graphicsEngine::drawGameBtns(){

    sf::Font font;
    font.loadFromFile("../src/Graphics/FreeMono.ttf");

    for(int i=0; i < m_gameBtns.size(); i++){

        sf::RectangleShape tmp_btn(m_gameBtns[i].m_size);

        tmp_btn.setPosition(m_gameBtns[i].m_location);
        tmp_btn.setFillColor(sf::Color::Green);
        tmp_btn.setOutlineColor(sf::Color::White);
        tmp_btn.setOutlineThickness(5);

        sf::Text tmp_btnTxt(m_gameBtns[i].m_text, font, 34);

        tmp_btnTxt.setColor(sf::Color::White);
        tmp_btnTxt.setStyle(sf::Text::Bold);
        tmp_btnTxt.setPosition(m_gameBtns[i].m_location + sf::Vector2f(10,10));

        m_window.draw(tmp_btn);
        m_window.draw(tmp_btnTxt);
    }
}
