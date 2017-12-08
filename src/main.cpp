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
    TowerTypeA() : TowerType("Tower1", 100, 10, 2.0, 2.0) { }
};


class TowerTypeA2 : public TowerType {
public:
    TowerTypeA2() : TowerType("Tower2", 100, 15, 2.0, 1.5) { }
};


class TowerTypeB : public TowerType {
public:
    TowerTypeB() : TowerType("TowerTypeB", 100, 5, 4.0, 2.0) { }
};


class TowerTypeB2 : public TowerType {
public:
    TowerTypeB2() : TowerType("TowerTypeB2", 150, 10, 4.0, 1.0) { }
};


class TowerTypeB3 : public TowerType {
public:
    TowerTypeB3() : TowerType("TowerTypeB3", 150, 20, 5.0, 2.0) { }
};


class EnemyType1 : public EnemyType {
public:
    EnemyType1() : EnemyType("Enemy1", 50, 100, 0.5, 100) { }
};


class EnemyType2 : public EnemyType {
public:
    EnemyType2() : EnemyType("Enemy2", 40, 110, 0.1, 100) { }
};

void sep(int length=80) {
    for (int i = 0; i < length; ++i) { std::cout <<  '='; }
    std::cout << std::endl;
}


/// Run tower defence game. Currently used for testing.
int main() {
    // Enemy type instances
    auto enemy_type_1 = EnemyType1();
    auto enemy_type_2 = EnemyType2();

    // Initial values
    int initial_money = 1000;
    double timestep = 0.01;
    int lives = 10;

    EnemySpawnInterval enemy_spawn_interval = {
            {1.0, &enemy_type_1},
            {2.0, &enemy_type_2}
    };

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


    std::cout << "Initializing GameMap" << std::endl;
    sep();
    auto game_map = game_map_from_file(
            "../src/maps/teromap.txt", &empty_tower_type, &root_tower_type);
    std::cout << game_map << std::endl;

    std::cout << "Initializing GameLevel" << std::endl;
    sep();
    auto game_level = GameLevel(initial_money, 0, 0, enemy_spawn_interval);

    std::cout << "Initializing GameEngine" << std::endl;
    sep();
    auto game_engine = new GameEngine(0, timestep, 0, 0, lives, game_level, game_map);

    // Set towers
    //TODO: remove this eventually when gui is ready.
    game_engine->upgrade_tower(0, 0, 0);
    game_engine->upgrade_tower(1, 1, 1);
    game_engine->upgrade_tower(2, 2, 1);



// =================== Graphics =======================


// ------------------------------------------------------ //

    // Create a window where stuff is drawn - 4:3 aspect ratio
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            "Graphics test");
    window.setKeyRepeatEnabled(false);

    graphicsEngine gE = graphicsEngine(window);

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
        switch( gE.m_currentScreen )
        {
            case mainScreen:
            {
                break;
            }
            case gameScreen:
            {
                // Window has to be cleaned every time to avoid overlap
                window.clear();
                // Let's draw the window and sidebar
                // Let's draw the tiles on the window
                gE.drawTiles(game_engine->game_map());
                // Let's draw the creatures
                gE.drawEnemies(game_map.enemies());
                // Let's show stats
                gE.addStatsWindow();
                gE.drawStats(dummyScore);
                gE.drawGameBtns();

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
                    switch(gE.m_currentScreen)   // What is the current screen state?
                    {
                        case mainScreen:    // We're in main screen
                        {
                            //gE.m_currentScreen = mainScreenPoller(window, windowSize);
                            int menuBtnPressed = gE.pollMainScreen();

                            switch( menuBtnPressed )
                            {
                                case 1:{break;}
                                case 0:{gE.m_currentScreen = gameScreen; break;}
                                case -1:{
                                    GameMap map1 = game_map_from_file("../src/maps/example.txt",
                                                                      &empty_tower_type, &root_tower_type);
                                    delete(game_engine);
                                    std::cout << "1" << std::endl;
                                    game_engine = new GameEngine(0, timestep, 0, 100, lives, game_level, map1);
                                    break;
                                }
                                case -2:{
                                    GameMap map2 = game_map_from_file("../src/maps/teromap.txt",
                                                                      &empty_tower_type, &root_tower_type);
                                    delete(game_engine);
                                    std::cout << "2" << std::endl;
                                    game_engine = new GameEngine(0, timestep, 0, 100, lives, game_level, map2);
                                    break;
                                }
                            }
                            break;
                        }
                        case gameScreen :   // We're in game screen
                        {
                            sf::Vector3f gameBtnPressed = gE.pollGameScreen();

                            switch( (int) gameBtnPressed.z ){
                                case 0: {
                                    window.clear();
                                    gE.m_currentScreen = mainScreen;
                                    gE.drawMenu();
                                    break;
                                }
                                case -1: {
                                    std::cout << "Select a place to build" << std::endl;
                                    gE.m_buildFlag = true;
                                    break;
                                }
                                case -2: {
                                    std::cout << "Select the tower to upgrade" << std::endl;
                                    gE.m_upgFlag = true;
                                    break;
                                }
                                case -3: {
                                    break;
                                }
                                default: {
                                    if( gE.m_buildFlag ){
                                        std::cout << "Built tower at " <<
                                                  gameBtnPressed.x << " ; " <<
                                                  gameBtnPressed.y << std::endl;
                                        gE.m_buildFlag = false;
                                    }else if( gE.m_upgFlag ){
                                        std::cout << "Upgraded tower at " <<
                                                  gameBtnPressed.x << " ; " <<
                                                  gameBtnPressed.y << std::endl;
                                        gE.m_upgFlag = false;
                                    } else{
                                        creatures[1].x = gE.m_tileSize.x * gameBtnPressed.x;
                                        creatures[1].y = gE.m_tileSize.y * gameBtnPressed.y;
                                    }
                                    break;
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
        creatures[1].y = fmod(creatures[1].y + displacement, gE.m_windowSize.y);

        dummyScore ++;

        gE.m_window.display();
    }


    return 0;
}
