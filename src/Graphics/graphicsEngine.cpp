#include "graphicsEngine.h"

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
    m_font.loadFromFile("../src/assets/FreeMono.ttf");

    addButtons();
}

void graphicsEngine::addButtons(){
    m_menuBtns.push_back(graphicsButton(
            sf::Vector2f(70, 150),
            sf::Vector2f(220, 120),
            std::string("New Game/\n Continue")
    ));
    m_menuBtns.push_back(graphicsButton(
            sf::Vector2f(70, 300),
            sf::Vector2f(100, 100),
            std::string("Map\n 1")
    ));
    m_menuBtns.push_back(graphicsButton(
            sf::Vector2f(190, 300),
            sf::Vector2f(100, 100),
            std::string("Map\n 2")
    ));

    m_menuBtns.push_back(graphicsButton(
            sf::Vector2f(70,70),
            sf::Vector2f(100, 60),
            std::string("Slow")
    ));
    m_menuBtns.push_back(graphicsButton(
            sf::Vector2f(190, 70),
            sf::Vector2f(100, 60),
            std::string("Fast")
    ));




    m_gameBtns.push_back(graphicsButton(
            sf::Vector2f(600, 500),
            sf::Vector2f(200, 100),
            std::string("MainMenu/\n  Pause")
    ));

    m_gameBtns.push_back(graphicsButton(
            sf::Vector2f(600, 400),
            sf::Vector2f(200, 100),
            std::string("Buy/\n  Upgrade")
    ));



    m_gameBtns.push_back(graphicsButton(
            sf::Vector2f(600, 205),
            sf::Vector2f(66, 55),
            std::string("F")
    ));

    m_gameBtns.push_back(graphicsButton(
            sf::Vector2f(666, 205),
            sf::Vector2f(66, 55),
            std::string("L")
    ));

    m_gameBtns.push_back(graphicsButton(
            sf::Vector2f(733, 205),
            sf::Vector2f(66, 55),
            std::string("W")
    ));
}

void graphicsEngine::drawMenu(){

    sf::Font font;
    font.loadFromFile("../src/assets/FreeMono.ttf");

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

    std::vector<int> score = high_score("../src/assets/score.txt");
    std::stringstream scorestream;
    scorestream << "High Scores:" << std::endl;
    auto it = score.begin();
    int i = 1;
    while (it != score.end()) {
        scorestream << i << ": " << *it << std::endl;
        it++;
        i++;
    }
    sf::Text scores(scorestream.str(), font, 20);
    scores.setColor(sf::Color::Black);
    scores.setStyle(sf::Text::Bold);
    scores.setPosition(sf::Vector2f(70, 440));
    m_window.draw(scores);


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
    font.loadFromFile("../src/assets/FreeMono.ttf");

    sf::Text txt1("Time: ", font, 20);
    txt1.setColor(sf::Color::Black);
    txt1.setStyle(sf::Text::Bold);
    txt1.setPosition(sf::Vector2f(610, 0));
    m_window.draw(txt1);

    sf::Text txt2("Score: ", font, 20);
    txt2.setColor(sf::Color::Black);
    txt2.setStyle(sf::Text::Bold);
    txt2.setPosition(610, 40);
    m_window.draw(txt2);

    sf::Text txt3("Money: ", font, 20);
    txt3.setColor(sf::Color::Black);
    txt3.setStyle(sf::Text::Bold);
    txt3.setPosition(610, 80);
    m_window.draw(txt3);

    sf::Text txt4("Lives: ", font, 20);
    txt4.setColor(sf::Color::Black);
    txt4.setStyle(sf::Text::Bold);
    txt4.setPosition(610, 120);
    m_window.draw(txt4);

    sf::Text txt5("Targeting: ", font, 24);
    txt5.setColor(sf::Color::Black);
    txt5.setStyle(sf::Text::Bold);
    txt5.setPosition(625, 170);
    m_window.draw(txt5);

}

void graphicsEngine::drawStats(GameEngine *game_engine) {
    sf::Font font;
    font.loadFromFile("../src/assets/FreeMono.ttf");

    std::stringstream ss;
    ss << (int) game_engine->time();

    sf::Text timestr(ss.str(), font, 20);
    timestr.setColor(sf::Color::Black);
    timestr.setPosition(sf::Vector2f(720, 0));
    m_window.draw(timestr);

    ss.str("");
    ss << game_engine->score();

    sf::Text scorestr(ss.str(), font, 20);
    scorestr.setColor(sf::Color::Black);
    scorestr.setPosition(720, 40);
    m_window.draw(scorestr);

    ss.str("");
    ss << game_engine->money();

    sf::Text moneystr(ss.str(), font, 20);
    moneystr.setColor(sf::Color::Black);
    moneystr.setPosition(720, 80);
    m_window.draw(moneystr);

    ss.str("");
    ss << game_engine->lives();

    sf::Text livesstr(ss.str(), font, 20);
    livesstr.setColor(sf::Color::Black);
    livesstr.setPosition(720, 120);
    m_window.draw(livesstr);
}


void graphicsEngine::drawEventBox(){
    sf::Font font;
    font.loadFromFile("../src/assets/FreeMono.ttf");

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
    if(m_gameEvents.back() != str || str == ""){
        if(str.back() == ')'){
            m_gameEvents.push_back(str);
            m_gameEvents.pop_front();
            m_gameEvents.push_back("");
            m_gameEvents.pop_front();
            m_gameEvents.push_back("");
            m_gameEvents.pop_front();
        }else{
            m_gameEvents.push_back(str);
            m_gameEvents.pop_front();
        }

    }
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
                        std::min(m_tileSize.x, m_tileSize.y) / 3, 3);
                tmpTower.setPosition(
                        sf::Vector2f((float) (i+0.15) * m_tileSize.x,
                                     (float) (j+0.17) * m_tileSize.y));

                switch(map.tiles().tile(i,j)->upgrade_level()){
                    case 1: tmpTower.setFillColor(sf::Color(100,100,100));
                        break;
                    case 2: tmpTower.setFillColor(sf::Color::Cyan);
                        break;
                    case 3: tmpTower.setFillColor(sf::Color::Magenta);
                        break;
                    default:tmpTower.setFillColor(sf::Color::White);
                        break;
                    }
                tmpTower.setOutlineThickness(
                        abs(map.tiles().tile(i,j)->tower()->time_since_last_attack()* 6 -
                                    map.tiles().tile(i,j)->tower()->attack_speed()* 6)
                    );
                tmpTower.setOutlineColor(sf::Color::Black);


                m_window.draw(tmpTower);
            }

        }
    }
}

void graphicsEngine::drawEnemies(Enemies enemies){

    sf::Color l_red(255, 128, 0);
    sf::Color d_red(255, 0, 128);
    sf::Color purple(255, 0, 255);
    sf::Color pink(0, 128, 128);

    for (auto &enemy : enemies) {
        sf::CircleShape tmpEnemy(std::min(m_tileSize.x, m_tileSize.y)  / 4);
        tmpEnemy.setPosition((enemy->x()-0.5) * m_tileSize.x + 15,
                             (enemy->y()-0.5) * m_tileSize.y + 15);
        std::string tmp_name = enemy->name();
        if (tmp_name == "Basic")        { tmpEnemy.setFillColor(l_red); }
        else if (tmp_name == "Tank")    { tmpEnemy.setFillColor(d_red); }
        else if (tmp_name == "Runner")  { tmpEnemy.setFillColor(purple); }
        else if (tmp_name == "Lord")    { tmpEnemy.setFillColor(sf::Color::Red); }
        else tmpEnemy.setFillColor(sf::Color::Black);

        tmpEnemy.setOutlineThickness( ((float) enemy->health() /
                (float) enemy->max_health())*10 );
        tmpEnemy.setOutlineColor(pink);

        m_window.draw(tmpEnemy);
    }
}

/*void graphicsEngine::drawAttack(Tower tower, Enemy enemy) {
    // TODO: Does not work
    float d = tower.distance(enemy);// sqrt(pow(tower.x()-enemy.x(),2) + pow(tower.y()-enemy.y(),2));
    float rot = asin(tower.y() - enemy.y() / d) / 3.141 * 180;
    if(tower.x() > enemy.x() && rot != 0){ rot *= 2; }
    else if( tower.x() > enemy.x() && rot == 0){ rot = 180;}

    std::cout << rot << std::endl;

    sf::RectangleShape tmpLine(sf::Vector2f(d*m_tileSize.x, 10));

    tmpLine.setPosition(tower.x()*m_tileSize.x, tower.y()*m_tileSize.y);
    tmpLine.setRotation(rot);
    tmpLine.setFillColor(sf::Color::Magenta);

    m_window.draw(tmpLine);
}
*/

void graphicsEngine::mouseBtnEventGame(GameEngine *game_engine){

    sf::Vector3f gameBtnPressed = pollGameScreen();

    switch( (int) gameBtnPressed.z ){
        case 0: {
            m_window.clear();
            addEvent("Game paused!");
            m_currentScreen = mainScreen;
            drawMenu();
            break;
        }
        case -1: {
            addEvent("Click on tile to\nbuild (100$) or\nupgrade\n(80/120/180$)");
            addEvent("");
            addEvent("");
            addEvent("");
            m_buildFlag = true;
            break;
        }
        case -2: {
            addEvent("Targeting: First");
            game_engine->change_targeting(target_first);
            break;
        }
        case -3: {
            game_engine->change_targeting(target_last);
            addEvent("Targeting: Last");
            break;
        }
        case -4: {
            game_engine->change_targeting(target_least_health);
            addEvent("Targeting: Weak");
            break;
        }
        default: {
            if( m_buildFlag ){
                game_engine->upgrade_tower(gameBtnPressed.x, gameBtnPressed.y, 0);
                m_buildFlag = false;
            }
            break;
        }
    }
}

void graphicsEngine::endMessage(bool win, bool done) {
    if (!done) {
        if (win) addEvent("You won!");
        else addEvent("You lost!");
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
    font.loadFromFile("../src/assets/FreeMono.ttf");

    for(int i=0; i < m_gameBtns.size(); i++){

        sf::RectangleShape tmp_btn(m_gameBtns[i].m_size);

        tmp_btn.setPosition(m_gameBtns[i].m_location);
        tmp_btn.setFillColor(sf::Color::Green);
        tmp_btn.setOutlineColor(sf::Color::White);
        tmp_btn.setOutlineThickness(5);

        sf::Text tmp_btnTxt(m_gameBtns[i].m_text, font, 30);

        tmp_btnTxt.setColor(sf::Color::White);
        tmp_btnTxt.setStyle(sf::Text::Bold);
        tmp_btnTxt.setPosition(m_gameBtns[i].m_location + sf::Vector2f(10,10));

        m_window.draw(tmp_btn);
        m_window.draw(tmp_btnTxt);
    }
}
