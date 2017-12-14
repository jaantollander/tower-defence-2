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

    for (int i = 0; i < 6; ++i) {
        m_gameEvents.push_back("");
    }

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

void graphicsEngine::drawMenu(){

    sf::Font font;
    font.loadFromFile("../src/Graphics/FreeMono.ttf");

    sf::Texture background;
    background.loadFromFile("../src/assets/tower2.jpg");
    sf::Sprite bg(background);
    m_window.draw(bg);


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

void graphicsEngine::addStatsWindow(){
    sf::RectangleShape statsArea(m_sideBarSize); // Stats
    statsArea.setPosition(m_mapSize.x, 0);
    statsArea.setFillColor(sf::Color(200,200,200));	// Light gray
    statsArea.setOutlineColor(sf::Color::White);
    statsArea.setOutlineThickness(5);
    m_window.draw(statsArea);

    sf::Font font;
    font.loadFromFile("../src/Graphics/FreeMono.ttf");

    sf::Text txt1("Time: ", font, 20);
    txt1.setColor(sf::Color::Black);
    txt1.setStyle(sf::Text::Bold);
    txt1.setPosition(sf::Vector2f(640, 0));
    m_window.draw(txt1);

    sf::Text txt2("Score: ", font, 20);
    txt2.setColor(sf::Color::Black);
    txt2.setStyle(sf::Text::Bold);
    txt2.setPosition(640, 70);
    m_window.draw(txt2);

    sf::Text txt3("Money: ", font, 20);
    txt3.setColor(sf::Color::Black);
    txt3.setStyle(sf::Text::Bold);
    txt3.setPosition(640, 140);
    m_window.draw(txt3);

    sf::Text txt4("Lives: ", font, 20);
    txt4.setColor(sf::Color::Black);
    txt4.setStyle(sf::Text::Bold);
    txt4.setPosition(640, 210);
    m_window.draw(txt4);
}

void graphicsEngine::drawStats(GameEngine *game_engine) {
    sf::Font font;
    font.loadFromFile("../src/Graphics/FreeMono.ttf");

    std::stringstream ss;
    ss << game_engine->time();

    sf::Text timestr(ss.str(), font, 20);
    timestr.setColor(sf::Color::Black);
    timestr.setPosition(sf::Vector2f(660, 25));
    m_window.draw(timestr);

    ss.str("");
    ss << game_engine->score();

    sf::Text scorestr(ss.str(), font, 20);
    scorestr.setColor(sf::Color::Black);
    scorestr.setPosition(660, 95);
    m_window.draw(scorestr);

    ss.str("");
    ss << game_engine->money();

    sf::Text moneystr(ss.str(), font, 20);
    moneystr.setColor(sf::Color::Black);
    moneystr.setPosition(660, 165);
    m_window.draw(moneystr);

    ss.str("");
    ss << game_engine->lives();

    sf::Text livesstr(ss.str(), font, 20);
    livesstr.setColor(sf::Color::Black);
    livesstr.setPosition(660, 235);
    m_window.draw(livesstr);
}

void graphicsEngine::drawEventBox(){
    sf::Font font;
    font.loadFromFile("../src/Graphics/FreeMono.ttf");

    sf::RectangleShape bg(sf::Vector2f(200,150));
    bg.setPosition(600, 260);
    bg.setFillColor(sf::Color::Black);

    m_window.draw(bg);


    for (int i = 0; i < m_gameEvents.size(); ++i) {
        sf::Text tmpStr(m_gameEvents[i], font, 18);
        tmpStr.setColor(sf::Color::White);
        tmpStr.setPosition(605, 265 + i*20);
        m_window.draw(tmpStr);
    }
}

void graphicsEngine::addEvent(std::string str){
    m_gameEvents.push_back(str);
    m_gameEvents.pop_front();
}

void graphicsEngine::drawTiles(GameMap map){

    sf::Color l_blue(0, 128, 255);

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
                case water: tmpTile.setFillColor(l_blue);
                    break;
                case undefined_tile_type: tmpTile.setFillColor(sf::Color::Black);
                    break;
            }
            m_window.draw(tmpTile);

            if( map.tiles().tile(i,j)->tower()->damage() > 0 ){
                sf::CircleShape tmpTower(
                        std::min(m_tileSize.x, m_tileSize.y) / 2.5, 3);
                tmpTower.setPosition(
                        sf::Vector2f((float) (i+0.12) * m_tileSize.x,
                                     (float) (j+0.12) * m_tileSize.y));

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

void graphicsEngine::drawEnemies(Enemies enemies){

    sf::Color l_red(255, 128, 0);
    sf::Color d_red(255, 0, 128);
    sf::Color purple(255, 0, 255);

    for (auto &enemy : enemies) {
        sf::CircleShape tmpEnemy(std::min(m_tileSize.x, m_tileSize.y)  / 3);
        tmpEnemy.setPosition((enemy->x()-0.5) * m_tileSize.x + 10,
                             (enemy->y()-0.5) * m_tileSize.y + 10);
        std::string tmp_name = enemy->name();
        if (tmp_name == "Basic")        { tmpEnemy.setFillColor(l_red); }
        else if (tmp_name == "Tank")    { tmpEnemy.setFillColor(d_red); }
        else if (tmp_name == "Runner")  { tmpEnemy.setFillColor(purple); }
        else if (tmp_name == "Lord")    { tmpEnemy.setFillColor(sf::Color::Red); }
        else tmpEnemy.setFillColor(sf::Color::Black);

        m_window.draw(tmpEnemy);
    }
}

void graphicsEngine::drawAttack(Tower tower, Enemy enemy) {
    
}


void graphicsEngine::mouseBtnEventGame(GameEngine *game_engine){

    sf::Vector3f gameBtnPressed = pollGameScreen();

    switch( (int) gameBtnPressed.z ){
        case 0: {
            m_window.clear();
            m_currentScreen = mainScreen;
            drawMenu();
            break;
        }
        case -1: {
            addEvent("Build for 100$");
            m_buildFlag = true;
            break;
        }
        case -2: {
            addEvent("Upgrade for");
            addEvent("80/120/180$");
            m_upgFlag = true;
            break;
        }
        case -3: {
            break;
        }
        default: {
            if( m_buildFlag ){
                game_engine->upgrade_tower(gameBtnPressed.x, gameBtnPressed.y, 0);
                m_buildFlag = false;
            }else if( m_upgFlag ){
                game_engine->upgrade_tower(gameBtnPressed.x, gameBtnPressed.y, 1);
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
