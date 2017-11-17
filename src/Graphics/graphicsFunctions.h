
enum Screens
{
    mainScreen,
    gameScreen
};

std::vector<sf::Vector2f> createAndDrawMenu(sf::RenderWindow &window,
                            sf::Vector2f windowSize);


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