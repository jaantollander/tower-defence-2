
enum Screens
{
    mainScreen,
    gameScreen
};

std::vector<sf::Vector2f> createAndDrawMenu(sf::RenderWindow &window,
                            sf::Vector2f windowSize);

void createAndDrawButton(sf::RenderWindow &window, sf::Vector2f buttonLU, sf::Vector2f buttonSize,
                         std::string &text, sf::Font &font);

void createAndDrawDrawables(sf::RenderWindow &window,
                            sf::Vector2f mapSize, sf::Vector2f sidebarSize);



void drawDrawables(sf::RenderWindow &window,
                   std::vector<sf::Drawable *> drawables);

void drawTiles(sf::RenderWindow &window, std::vector< std::vector<int> > &map,
               int tileAmount, sf::Vector2f tileSize);

void drawCreatures(sf::RenderWindow &window,
                   std::vector<sf::Vector3f> creatures, sf::Vector2f tileSize);

void mainScreenPoller(sf::RenderWindow &window, sf::Vector2f windowSize,
                            Screens &currentScreen);

void gameScreenPoller(sf::RenderWindow &window, std::vector<sf::Vector3f> &creatures,
                            Screens &currentScreen);

void drawStats(sf::RenderWindow &window, int stats);