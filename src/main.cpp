#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "engine.h"
#include "assets/towers.h"
#include "assets/enemies.h"


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
            map_path = "../src/assets/map1.txt";
            break;
        }
        case map2: {
            map_path = "../src/assets/map2.txt";
            break;
        }
        default:
            throw std::exception();
    }
    auto game_map = game_map_from_file(map_path, empty_tower_type, root_tower_type);
    auto game_level = GameLevel(initial_money, initial_lives, 0, enemy_spawn_interval);
    return new GameEngine(0, timestep, 0, game_level, game_map);
}


/// Run tower defence game.
int main()  {
    // Enemy type instances
    auto basic_enemy    = EnemyType1();
    auto tank           = EnemyType2();
    auto runner         = EnemyType3();
    auto lord           = EnemyType4();
    auto king           = EnemyType5();

    // Initial values
    const int initial_money = 400;
    double timestep = 0.012;
    const int initial_lives = 10;


    //Spawn time and which enemy type to spawn
    EnemySpawnInterval enemy_spawn_interval = {
            {4.0, &basic_enemy},
            {5.0, &basic_enemy},
            {8.0, &basic_enemy},
            {9.0, &basic_enemy},
            {12.0, &basic_enemy},
            {13.0, &basic_enemy},
            {19.0, &basic_enemy},
            {20.0, &basic_enemy},
            {23.0, &basic_enemy},
            {24.0, &basic_enemy},



            {50.0, &basic_enemy},
            {51.0, &basic_enemy},
            {52.0, &basic_enemy},
            {57.0, &tank},
            {61.0, &tank},
            {64.0, &basic_enemy},
            {65.0, &basic_enemy},
            {70.0, &tank},
            {73.0, &tank},
            {75.0, &runner},


            {115.0, &runner},
            {116.0, &runner},
            {117.0, &runner},
            {120.0, &runner},
            {121.0, &runner},
            {122.0, &runner},
            {130.0, &tank},
            {131.0, &tank},
            {132.0, &tank},
            {135.0, &lord},
            {142.0, &lord},
            {145.0, &lord},


            {180.0, &basic_enemy},
            {180.5, &basic_enemy},
            {181.0, &basic_enemy},
            {181.5, &basic_enemy},
            {182.0, &tank},
            {188.0, &basic_enemy},
            {188.5, &basic_enemy},
            {189.0, &basic_enemy},
            {189.5, &basic_enemy},
            {190.0, &tank},
            {196.0, &basic_enemy},
            {196.5, &basic_enemy},
            {197.0, &basic_enemy},
            {197.5, &basic_enemy},
            {198.0, &tank},
            {204.0, &basic_enemy},
            {204.5, &basic_enemy},
            {205.0, &basic_enemy},
            {205.5, &basic_enemy},
            {206.0, &lord},
            {207.0, &lord},


            {242.0, &lord},
            {244.0, &king},
            {248.0, &lord},
            {250.0, &king},
            {254.0, &lord},
            {256.0, &king},


            {280.0, &king},
            {282.0, &king},
            {288.0, &tank},
            {289.0, &tank},
            {290.0, &tank},
            {291.0, &tank},
            {292.0, &tank},
            {296.0, &king},
            {297.0, &king},
            {298.0, &king},
            {299.0, &king},
            {300.0, &king},
            {301.0, &king},
            {302.0, &king}

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
    tower_type_b.add_upgrade_option(&tower_type_b2);

    // Initialize game engine and state
    auto game_engine = new_game_engine(
            map1, &empty_tower_type, &root_tower_type, initial_money,
            initial_lives, enemy_spawn_interval, timestep);
    auto state = level_unfinished;
    bool score_saved = false;

    // =================== Graphics =======================

    // Create a window where stuff is drawn - 4:3 aspect ratio
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics test");
    // Listen only to singel key strokes (doesn't work well)
    window.setKeyRepeatEnabled(false);

    // Initialize graphics engine
    graphicsEngine gE = graphicsEngine(window);

    // Create and draw the Main menu
    gE.drawMenu();

    // Allocate game Buttons to be defined later
    std::vector<sf::Vector2f> gameBtns;

    // Start a clock and frame limit handling the game time
    sf::Clock clock;
    gE.m_window.setFramerateLimit(120);

    // While window has not been closed, keep on going
    while (window.isOpen()) {
        // Draw the screens
        switch(gE.m_currentScreen) {
            // Main screen - Do nothing (already exists)
            case mainScreen:
                break;
            // Game screen - Update the graphics
            case gameScreen: {
                // Clear window to avoid overlap
                window.clear();
                // Draw the tiles, path and towers
                gE.drawTiles(game_engine->game_map());
                // Draw the enemies
                gE.drawEnemies(game_engine->game_map().enemies());
                // Draw game stats, events texts and buttons
                gE.addStatsWindow();
                gE.drawStats(game_engine);
                gE.drawEventBox();
                gE.drawGameBtns();
                break;
            }
        }

        // Sniff for window events
        sf::Event event;

        // Something was clicked
        while(window.pollEvent(event)) {
            switch (event.type) {
                // Window was closed
                case sf::Event::Closed : {
                    window.close();
                    break;
                }
                // LMouseButton was clicked
                case sf::Event::MouseButtonReleased : {
                    switch(gE.m_currentScreen) {
                        // Menu was clicked
                        case mainScreen: {
                            int menuBtnPressed = gE.pollMainScreen();
                            // Which button was clicked
                            switch(menuBtnPressed) {
                                case 1: {
                                    break;
                                }
                                case 0: {
                                    gE.m_currentScreen = gameScreen;
                                    gE.addEvent("Game has started!");
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
                                case -3: {
                                    std::cout << "Normal"<< std::endl;
                                    game_engine->change_game_speed(normal);
                                    break;
                                }
                                case -4: {
                                    std::cout << "Fast"<< std::endl;
                                    game_engine->change_game_speed(fast);
                                    break;
                                }
                                default:
                                    break;
                            }
                            break;
                        }
                        // Game screen was clicked
                        case gameScreen : {
                            gE.mouseBtnEventGame(game_engine);
                            break;
                        }
                    }
                    break;
                }
            }
        }

        // Restart the clock (not used)
        sf::Time elapsedTime = clock.restart();

        // Advance the game
        if (gE.m_currentScreen == gameScreen) {
            // Check the game state
            switch (state) {
                case level_completed:
                    gE.endMessage(true, score_saved);
                    if (not score_saved) {
                        update_high_score("../src/assets/score.txt", *game_engine);
                        score_saved = true;
                    }
                    break;
                case game_over:
                    gE.endMessage(false, score_saved);
                    if (not score_saved) {
                        update_high_score("../src/assets/score.txt", *game_engine);
                        score_saved = true;
                    }
                    break;
                // Advance the game
                default: {
                    state = game_engine->update(gE);
                    break;
                }
            }
        }

        // Make all new graphics visible
        gE.m_window.display();
    }


    return 0;
}
