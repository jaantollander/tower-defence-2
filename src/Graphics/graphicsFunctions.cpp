
std::vector<sf::Vector2f> createAndDrawMenu(sf::RenderWindow &window,
                                            sf::Vector2f windowSize)
{
    std::vector<sf::Vector2f> buttonLocation; // In for Left-Upper, Right-Bottom
    std::vector<sf::Drawable *> drawables;

        // Create a box for a 'button'
    sf::Vector2f buttonLU = windowSize / 5.f;
        buttonLocation.push_back(buttonLU);
    sf::Vector2f buttonSize = sf::Vector2f(160,120);
    sf::Vector2f buttonRB = buttonLU + buttonSize;
        buttonLocation.push_back(buttonRB);

    sf::RectangleShape button(buttonSize);
        button.setPosition(buttonLU);
        button.setFillColor(sf::Color::Green);
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(5);
    drawables.push_back(&button);

        // Create text inside the box
    sf::Font font;	// A font type has to be downloaded
        font.loadFromFile("FreeMono.ttf");

    sf::Text buttonText("Start", font, 34);
        buttonText.setColor(sf::Color::White);
        buttonText.setStyle(sf::Text::Bold);
        buttonText.setPosition(buttonLU * (float) 1.2);
    drawables.push_back(&buttonText);


    drawDrawables(window, drawables);

    return buttonLocation;

}


void createAndDrawDrawables(sf::RenderWindow &window,
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

void mainScreenPoller(sf::RenderWindow &window, sf::Vector2f windowSize,
                                Screens &currentScreen)
{
    std::vector <sf::Vector2f> asd = createAndDrawMenu(window, windowSize);

    std::cout << "2" << std::endl;

    sf::Vector2i mp = sf::Mouse::getPosition(window); // MousePosition
    // Was it inside a button?
    if( mp.x > asd[0].x && mp.y > asd[0].y &&
        mp.x < asd[1].x && mp.y < asd[1].y )
    {
        currentScreen = gameScreen;     // Yes -> Start the game
    }
}

void gameScreenPoller(sf::RenderWindow &window, std::vector<sf::Vector3f> &creatures,
                            Screens &currentScreen)
{
    if( sf::Mouse::getPosition(window).x < 600 )
    {
        creatures[1].x = sf::Mouse::getPosition(window).x;
    }
    else
    {
        currentScreen = mainScreen;
    }
}