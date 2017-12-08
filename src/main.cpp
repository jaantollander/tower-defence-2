#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "engine.h"
#include "Graphics/graphicsEngine.h"


/// Empty tower type. Cannot be upgraded into any tower.
class EmptyTowerType : public TowerType {
public:
    EmptyTowerType() : TowerType("EmptyTower", 0, 0, 0, 0) { }
};


/// Empty tower type. Can be upgraded into a tower defined by upgrade options.
class RootTowerType : public TowerType {
public:
    RootTowerType() : TowerType("RootTower", 0, 0, 0, 0) { }
};


class TowerTypeA : public TowerType {
public:
    TowerTypeA() : TowerType("Tower1", 300, 20, 4, 8) { }
};


class TowerTypeA2 : public TowerType {
public:
    TowerTypeA2() : TowerType("Tower2", 0, 0, 0, 0) { }
};


class TowerTypeB : public TowerType {
public:
    TowerTypeB() : TowerType("TowerTypeB", 100, 10, 4, 5) { }
};


class TowerTypeB2 : public TowerType {
public:
    TowerTypeB2() : TowerType("TowerTypeB2", 0, 0, 0, 0) { }
};


class TowerTypeB3 : public TowerType {
public:
    TowerTypeB3() : TowerType("TowerTypeB3", 0, 0, 0, 0) { }
};


class EnemyType1 : public EnemyType {
public:
    EnemyType1() : EnemyType("Enemy1", 50, 100, 1, 40) { }
};


class EnemyType2 : public EnemyType {
public:
    EnemyType2() : EnemyType("Enemy2", 0, 0, 0, 0) { }
};

void sep(int length=80) {
    for (int i = 0; i < length; ++i) { std::cout <<  '='; }
    std::cout << std::endl;
}


/// Run tower defence game. Currently used for testing.
int main() {
    // Tower type instances
    auto empty_tower_type = EmptyTowerType();
    auto root_tower_type = RootTowerType();

    auto tower_type_a = TowerTypeA();
    auto tower_type_a2 = TowerTypeA2();

    auto tower_type_b = TowerTypeB();
    auto tower_type_b2 = TowerTypeB2();
    auto tower_type_b3 = TowerTypeB3();

    // Upgrade options
    root_tower_type.add_upgrade_option(&tower_type_a);
    tower_type_a.add_upgrade_option(&tower_type_a2);
    root_tower_type.add_upgrade_option(&tower_type_b);
    tower_type_b.add_upgrade_option(&tower_type_b2);
    tower_type_b.add_upgrade_option(&tower_type_b3);

    // Enemy type instances
    auto enemy_type_1 = EnemyType1();
    auto enemy_type_2 = EnemyType2();

    std::cout << "Initializing GameMap" << std::endl;
    sep();
    auto game_map = game_map_from_file(
            "src/maps/example.txt", &empty_tower_type, &root_tower_type);
    std::cout << game_map << std::endl;

    std::cout << "Initializing GameLevel" << std::endl;
    sep();
    EnemySpawnInterval enemy_spawn_interval = {
            {1.0, &enemy_type_1},
            {2.0, &enemy_type_2}
    };
    auto game_level = GameLevel(1000, 0, 0, enemy_spawn_interval);

    std::cout << "Initializing GameEngine" << std::endl;
    sep();
    auto game_engine = GameEngine(0, 0.01, 0, 0, 10, game_level, game_map);

    // Set towers
    //TODO: fix x and y coordinates
    game_engine.upgrade_tower(2, 3, 0);
    game_engine.upgrade_tower(4, 2, 1);

    // Set enemies
    //TODO: fix x and y coordinates
    Enemy e1 = enemy_type_1.create_enemy(3, 0);
    Enemy e2 = enemy_type_1.create_enemy(3, 1);
    Enemy e3 = enemy_type_1.create_enemy(3, 2);
    game_engine.add_enemy(&e1);
    game_engine.add_enemy(&e2);
    game_engine.add_enemy(&e3);

    std::cout << "Tower attack test.." << std::endl;

    game_engine.towers_attack();

    game_engine.update_high_score("src/score.txt");


// =================== Graphics =======================


    // define the sizes of different areas
    // TODO: Kaikki yhdeksi objektiksi jonka voi sitten antaa inputtina funktioille
    sf::Vector2f mapSize(600.f, 600.f);
    sf::Vector2f sidebarSize(200.f, mapSize.y);
    sf::Vector2f windowSize(mapSize.x + sidebarSize.x, mapSize.y);

// ------------------------------------------------------ //

    // Create a window where stuff is drawn - 4:3 aspect ratio
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
                            "Graphics test");
    window.setKeyRepeatEnabled(false);

    // Enumerate different screens of the game
    Screens currentScreen = mainScreen;

    graphicsEngine gE = graphicsEngine(window);

// ------------------------------------------------------ //

    // Make tiles on the basis of map size
    // TODO: This should be done on the basis of the map Class
    int tileAmount = 10; // Assume square map with even number of tiles
    sf::Vector2f tileSize(mapSize.x / tileAmount, mapSize.y / tileAmount);

    // Colour the tiles according to map info

    // Create a random map
    std::vector< std::vector<int> > randomMap(tileAmount);
    for (int i = 0; i < tileAmount; ++i) {
        for (int j = 0; j < tileAmount; ++j) {
            randomMap[i].push_back(rand() % 3);
        }
    }


// ------------------------------------------------------ //

    // Create some creatures to be drawn on tiles
    std::vector<sf::Vector3f> creatures;
    creatures.push_back(sf::Vector3f(60, 60, 1 ));
    creatures.push_back(sf::Vector3f(300, 120, 2 ));

// ------------------------------------------------------ //
    // Draw (and update) the objects to the screen

    // Create the menu
    //std::vector<sf::Vector2f> menuBtns = createAndDrawMenu(window, windowSize);
    gE.drawMenu();
    std::vector<sf::Vector2f> gameBtns;
    int dummyScore = 1;
    // Start a clock
    sf::Clock clock;
    // While window has not been closed, keep on going
    while (window.isOpen())
    {

        // Window has to be cleaned every time to avoid overlap
        //window.clear();

        // Draw the screens
        switch( currentScreen )
        {
            case mainScreen:
            {
                //std::vector<sf::Vector2f> menuBtns = createAndDrawMenu(window, windowSize);
                //gE.drawMenu();
                break;
            }
            case gameScreen:
            {
                // Window has to be cleaned every time to avoid overlap
                window.clear();
                // Let's draw the window and sidebar
                //gameBtns = createAndDrawGame(window, mapSize, sidebarSize);
                // Let's draw the tiles on the window
                //drawTiles(window, randomMap, tileAmount, tileSize);
                gE.drawTiles(randomMap);
                // Let's draw the creatures
                //drawCreatures(window, creatures, tileSize);
                gE.drawCreatures(creatures);
                // Let's show stats
                //drawStats(window, dummyScore);
                gE.addStatsWindow();
                gE.drawStats(dummyScore);
                break;
            }
        }

        // Sniff for window events
        sf::Event event;

        // Something was clicked ->
        while(window.pollEvent(event)) {
            switch (event.type)
            {
                case sf::Event::Closed : // Window was closed
                {
                    window.close();
                    break;
                }

                case sf::Event::MouseButtonReleased : // LMouseButton was clicked
                {
                    switch(currentScreen)   // What is the current screen state?
                    {
                        case mainScreen:    // We're in main screen
                        {
                            currentScreen = mainScreenPoller(window, windowSize);
                            break;
                        }
                        case gameScreen :   // We're in game screen
                        {
                            sf::Vector2f gameBtnPressed = gameScreenPoller(window, creatures, gameBtns);

                            switch( (int) gameBtnPressed.x ){
                                case -1: {
                                    window.clear();
                                    currentScreen = mainScreen;
                                    createAndDrawMenu(window, windowSize);
                                }
                                default: {
                                    creatures[1].x = gameBtnPressed.x;
                                    creatures[1].y = gameBtnPressed.y;
                                }
                            }


                            break;
                        }
                    }
                    break;
                }
            }
        }

        // What's our in-game time?
        sf::Time elapsedTime = clock.restart();
        // Update creatures' positions
        float displacement = 100 * elapsedTime.asSeconds(); // pix/s * s = pix
        creatures[1].y = fmod(creatures[1].y + displacement, windowSize.y);

        dummyScore ++;

        window.display();

    }


    return 0;
}
