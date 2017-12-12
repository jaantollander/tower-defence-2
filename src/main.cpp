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
    EnemyType1() : EnemyType("Enemy1", 50, 100, 0.5, 1000) { }
};

class EnemyType2 : public EnemyType {
public:
    EnemyType2() : EnemyType("Enemy2", 40, 110, 0.35, 1000) { }
};

class EnemyType3 : public EnemyType {
public:
    EnemyType3() : EnemyType("Enemy2", 60, 200, 0.45, 2000) { }
};

enum MapChoices {
    map1,
    map2
};

/// Initialize new game engine
GameEngine *new_game_engine(MapChoices map_choice, TowerType *empty_tower_type,
        TowerType *root_tower_type, int initial_money, int initial_lives,
        EnemySpawnInterval &enemy_spawn_interval, double timestep) {
    std::string map_path;
    switch (map_choice) {
        case map1: {
            map_path = "../src/maps/map1.txt";
            break;
        }
        case map2: {
            map_path = "../src/maps/map2.txt";
            break;
        }
        default:
            throw std::exception();
    }
    auto game_map = game_map_from_file(map_path, empty_tower_type, root_tower_type);
    auto game_level = GameLevel(initial_money, initial_lives, 0, enemy_spawn_interval);
    return new GameEngine(0, timestep, 0, game_level, game_map);
}


/// Run tower defence game. Currently used for testing.
int main()  {
    // Enemy type instances
    auto enemy_type_1 = EnemyType1();
    auto enemy_type_2 = EnemyType2();
    auto enemy_type_3 = EnemyType3();

    // Initial values
    const int initial_money = 600;
    const double timestep = 0.01;
    const int initial_lives = 10;

    EnemySpawnInterval enemy_spawn_interval = {
            {4.0, &enemy_type_1},
            {8.0, &enemy_type_2},
            {13.0, &enemy_type_3},
            {18.0, &enemy_type_1},
            {21.0, &enemy_type_2},
            {23.0, &enemy_type_3},
            {25.0, &enemy_type_1},
            {27.0, &enemy_type_2},
            {28.0, &enemy_type_3},
            {29.0, &enemy_type_2},
    };

    // Tower type instances
    auto empty_tower_type = EmptyTowerType();
    auto root_tower_type = RootTowerType();

    auto tower_type_a = TowerTypeA();
    auto tower_type_a2 = TowerTypeA2();
    auto tower_type_b = TowerTypeB();

    auto tower_type_b2 = TowerTypeB2();
    auto tower_type_b3 = TowerTypeB3();

    // Define tower hierarchy (upgrade options)
    root_tower_type.add_upgrade_option(&tower_type_a);
    tower_type_a.add_upgrade_option(&tower_type_a2);
    tower_type_a2.add_upgrade_option(&tower_type_b);
//    tower_type_b.add_upgrade_option(&tower_type_b2);
//    tower_type_b2.add_upgrade_option(&tower_type_b3);

    auto game_engine = new_game_engine(
            map1, &empty_tower_type, &root_tower_type, initial_money,
            initial_lives, enemy_spawn_interval, timestep);
    auto state = level_unfinished;
    bool score_saved = false;

// =================== Graphics =======================


// ------------------------------------------------------ //

    // Create a window where stuff is drawn - 4:3 aspect ratio
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics test");
    window.setKeyRepeatEnabled(false);

    graphicsEngine gE = graphicsEngine(window);

// ------------------------------------------------------ //
    // Draw (and update) the objects to the screen

    // Create the menu
    gE.drawMenu();
    std::vector<sf::Vector2f> gameBtns;
    // Start a clock
    sf::Clock clock;
    // While window has not been closed, keep on going
    while (window.isOpen()) {
        // Draw the screens
        //TODO: refactor to screen_event_handler function
        switch(gE.m_currentScreen) {
            case mainScreen:
                break;
            case gameScreen: {
                // Window has to be cleaned every time to avoid overlap
                window.clear();
                // Let's draw the window and sidebar
                // Let's draw the tiles on the window
                gE.drawTiles(game_engine->game_map());
                // Let's draw the creatures
                gE.drawEnemies(game_engine->game_map().enemies());
                // Let's show stats
                gE.addStatsWindow();
                gE.drawStats(game_engine);
                gE.drawGameBtns();
                break;
            }
        }

        // Sniff for window events
        sf::Event event;

        // Something was clicked ->
        //TODO: refactor to poll_event_handler function
        while(window.pollEvent(event)) {
            switch (event.type) {
                // Window was closed
                case sf::Event::Closed : {
                    window.close();
                    break;
                }
                // LMouseButton was clicked
                case sf::Event::MouseButtonReleased : {
                    // What is the current screen state?
                    switch(gE.m_currentScreen) {
                        case mainScreen: {
                            int menuBtnPressed = gE.pollMainScreen();
                            switch(menuBtnPressed) {
                                case 1: {
                                    break;
                                }
                                case 0: {
                                    gE.m_currentScreen = gameScreen;
                                    break;
                                }
                                case -1: {
                                    delete(game_engine);
                                    state = level_unfinished;
                                    score_saved = false;
                                    game_engine = new_game_engine(
                                            map1, &empty_tower_type,
                                            &root_tower_type,
                                            initial_money,
                                            initial_lives, enemy_spawn_interval,
                                            timestep);
                                    break;
                                }
                                case -2: {
                                    delete(game_engine);
                                    state = level_unfinished;
                                    score_saved = false;
                                    game_engine = new_game_engine(
                                            map2, &empty_tower_type,
                                            &root_tower_type,
                                            initial_money,
                                            initial_lives, enemy_spawn_interval,
                                            timestep);
                                    break;
                                }
                                default:
                                    break;
                            }
                            break;
                        }
                        case gameScreen : {
                            gE.mouseBtnEventGame(game_engine);
                            break;
                        }
                    }
                    break;
                }
            }
        }

        // What's our in-game time?
        sf::Time elapsedTime = clock.restart();

        // Update game logic
        if (gE.m_currentScreen == gameScreen) {
            switch (state) {
                case level_completed:
                    //TODO: handle level completed
                    if (not score_saved) {
                        game_engine->update_high_score("../src/score.txt");
                        score_saved = true;
                    }
                    break;
                case game_over:
                    //TODO: handle game over
                    if (not score_saved) {
                        game_engine->update_high_score("../src/score.txt");
                        score_saved = true;
                    }
                    break;
                default: {
                    state = game_engine->update();
                    break;
                }
            }
        }

        gE.m_window.display();
    }


    return 0;
}
