
std::vector<sf::Vector2f> createAndDrawMenu(sf::RenderWindow &window,
                                            sf::Vector2f windowSize)
{
    std::vector<sf::Vector2f> buttonLocations; // Upper left corner
    std::vector<sf::Vector2f> buttonSizes; // Width, height
    std::vector<std::string>  buttonTexts; // Upper left corner
    //std::vector<sf::Drawable *> drawables;


        // Create Start button
    buttonLocations.push_back(sf::Vector2f(100, 200));
    buttonSizes.push_back(sf::Vector2f(160,120));
        buttonLocations.push_back(buttonLocations.back() + buttonSizes.back());
    buttonTexts.push_back("Start");

        // Create Map1 selector
    buttonLocations.push_back(sf::Vector2f(330, 100));
    buttonSizes.push_back(sf::Vector2f(100,100));
    buttonLocations.push_back(buttonLocations.back() + buttonSizes.back());
    buttonTexts.push_back("Map\n 1");

        // Create Map2 selector
    buttonLocations.push_back(sf::Vector2f(330, 230));
    buttonSizes.push_back(sf::Vector2f(100,100));
    buttonLocations.push_back(buttonLocations.back() + buttonSizes.back());
    buttonTexts.push_back("Map\n 2");

    // A font type has to be downloaded
    sf::Font font;
    font.loadFromFile("FreeMono.ttf");

    for(int i = 0; i < buttonTexts.size(); i++){
        createAndDrawButton(window, buttonLocations[i*2], buttonSizes[i], buttonTexts[i], font);
    }


    //drawDrawables(window, drawables);

    return buttonLocations;
}


void createAndDrawButton(sf::RenderWindow &window, sf::Vector2f buttonLU, sf::Vector2f buttonSize,
                         std::string &text, sf::Font &font){
    std::vector<sf::Drawable *> drawables;

    sf::RectangleShape button(buttonSize);
    button.setPosition(buttonLU);
    button.setFillColor(sf::Color::Green);
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(5);

    drawables.push_back(&button);

    sf::Text buttonText(text, font, 34);
    buttonText.setColor(sf::Color::White);
    buttonText.setStyle(sf::Text::Bold);
    buttonText.setPosition(buttonLU + sf::Vector2f(10,10));

    drawables.push_back(&buttonText);

    drawDrawables(window, drawables);
}


std::vector<sf::Vector2f> createAndDrawGame(sf::RenderWindow &window,
                            sf::Vector2f mapSize, sf::Vector2f sidebarSize)
{
    std::vector<sf::Drawable *> drawables;

    // Create two rectangles for the basis of map and status parts
    sf::RectangleShape mapArea(mapSize);
        mapArea.setFillColor(sf::Color::Green);
        mapArea.setOutlineColor(sf::Color::Black);
        mapArea.setOutlineThickness(5);
    drawables.push_back(&mapArea);

    sf::RectangleShape statsArea(sidebarSize); // Stats
        statsArea.setPosition(mapSize.x, 0);
        statsArea.setFillColor(sf::Color(200,200,200));	// Light gray
        statsArea.setOutlineColor(sf::Color::White);
        statsArea.setOutlineThickness(5);
    drawables.push_back(&statsArea);


// ------------------------------------------------------ //

    // Create text fields that are needed

    sf::Font font;	// A font type has to be downloaded
    font.loadFromFile("FreeMono.ttf");

    sf::Text points("Points: ", font, 24);
    points.setColor(sf::Color::Black);
    points.setStyle(sf::Text::Bold);
    points.setPosition(sf::Vector2f(640, 50));
    drawables.push_back(&points);

    sf::Text round("Round: ", font, 24);
    round.setColor(sf::Color::Black);
    round.setStyle(sf::Text::Bold);
    round.setPosition(650, 150);
    drawables.push_back(&round);

    sf::Text resources("Resources: ", font, 24);
    resources.setColor(sf::Color::Black);
    resources.setStyle(sf::Text::Bold);
    resources.setPosition(620, 250);
    drawables.push_back(&resources);


    drawDrawables(window, drawables);

    std::string menuString = "MainMenu";
    createAndDrawButton(window, sf::Vector2f(600,500), sf::Vector2f(200,100), menuString, font);

    std::vector<sf::Vector2f> buttonLocations; // Upper left corner
    buttonLocations.push_back(sf::Vector2f(600,500));
    buttonLocations.push_back(sf::Vector2f(600,500)+sf::Vector2f(200,100));

    return buttonLocations;

}


void drawDrawables(sf::RenderWindow &window, std::vector<sf::Drawable *> drawables)
{
    std::vector<sf::Drawable *>::iterator it = drawables.begin();
    for( ; it != drawables.end(); it++ )
    {
        window.draw(**it);
    }
}

// Iterate through map and draw the tiles
void drawTiles(sf::RenderWindow &window, std::vector< std::vector<int> > &map,
               int tileAmount, sf::Vector2f tileSize)
{
    for (int i = 0; i < tileAmount; ++i) {
        for (int j = 0; j < tileAmount; ++j) {
            sf::RectangleShape tmpTile(tileSize);
            tmpTile.setPosition(j*tileSize.x, i*tileSize.y); // OBS j,i !
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
            window.draw(tmpTile);
        }
    }
}


void drawCreatures(sf::RenderWindow &window,
                   std::vector<sf::Vector3f> creatures, sf::Vector2f tileSize)
{
    for (int i = 0; i < creatures.size(); ++i) {
        sf::CircleShape tmpCreature(std::min(tileSize.x, tileSize.y) / 2);
        tmpCreature.setPosition(creatures[i].x, creatures[i].y); // OBS j,i !

        switch((int) creatures[i].z) {
            case 1:
                tmpCreature.setFillColor(sf::Color::Blue);
                break;
            case 2:
                tmpCreature.setFillColor(sf::Color::Yellow);
                break;
        }

        window.draw(tmpCreature);
    }
}

Screens mainScreenPoller(sf::RenderWindow &window, sf::Vector2f windowSize)
{
    std::vector <sf::Vector2f> menuButtons = createAndDrawMenu(window, windowSize);

    sf::Vector2i mp = sf::Mouse::getPosition(window); // MousePosition

        // Was mouse inside which button?
    int idx = 0;
    for(; idx < menuButtons.size(); idx+=2){
        if( mp.x > menuButtons[idx].x && mp.y > menuButtons[idx].y &&
            mp.x < menuButtons[idx+1].x && mp.y < menuButtons[idx+1].y ){
            break;
        }
    }

    switch(idx/2){
        case 0:{
            Screens currentScreen = gameScreen;
            return currentScreen;
        }
        case 1:{
            std::cout << "Map set to 1" << std::endl;
            break;
        }
        case 2: {
            std::cout << "Map set to 2" << std::endl;
            break;
        }
    }
    Screens currentScreen = mainScreen;
    return currentScreen;

}

sf::Vector2f gameScreenPoller(sf::RenderWindow &window,
                                           std::vector<sf::Vector3f> &creatures,
                                           std::vector<sf::Vector2f> gameBtns){

    sf::Vector2f btnPressed;

    int mPosx = sf::Mouse::getPosition(window).x;
    int mPosy = sf::Mouse::getPosition(window).y;

    if( mPosx < 600 )
    {
        btnPressed.x = mPosx;
        btnPressed.y = mPosy;
    }
    else
    {       // Find which button was pressed - indexing -1,-1 for menu etc.
        for(float i=1; i < gameBtns.size(); i+=2){
            if( mPosx > gameBtns[i-1].x && mPosy > gameBtns[i-1].y &&
                mPosx < gameBtns[i].x && mPosy < gameBtns[i].y ){

                btnPressed.x = -i/2 - 0.5;
                btnPressed.y = -i/2 - 0.5;

                std::cout << btnPressed.x << std::endl;
                break;
            }
        }
    }
    return btnPressed;
}


    // TODO: Switch int to Stats and write ss << stats.getPoints() etc.
void drawStats(sf::RenderWindow &window, int stats){

    std::vector<sf::Drawable *> drawables;

    sf::Font font;	// A font type has to be downloaded
    font.loadFromFile("FreeMono.ttf");

    std::stringstream ss;
    ss << stats;

    sf::Text points(ss.str(), font, 22);
    points.setColor(sf::Color::Black);
    points.setPosition(sf::Vector2f(660, 80));
    drawables.push_back(&points);

    ss.str("");
    ss << 1;

    sf::Text round(ss.str(), font, 24);
    round.setColor(sf::Color::Black);
    round.setPosition(660, 180);
    drawables.push_back(&round);

    ss.str("");
    ss << 100;

    sf::Text resources(ss.str(), font, 24);
    resources.setColor(sf::Color::Black);
    resources.setPosition(660, 280);
    drawables.push_back(&resources);

    drawDrawables(window, drawables);

}