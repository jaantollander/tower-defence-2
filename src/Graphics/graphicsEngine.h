#ifndef TOWER_DEFENCE_2_GRAPHICS_ENGINE_H
#define TOWER_DEFENCE_2_GRAPHICS_ENGINE_H

#include "graphicsButton.h"
#include <sstream>
#include <queue>
#include "graphicsFunctions.h"
#include "../map/map.h"
#include "../engine.h"

// Deferred declaration
class GameEngine;

/// Graphics engine class
class graphicsEngine{
public:
    /// Initialize graphics engine with a predefined app window
    explicit graphicsEngine(sf::RenderWindow &window);

    void addButtons();

    /// Draw contents of the main menu
    void drawMenu();

    /// Create static contents of game stats area
    void addStatsWindow();

    /// Draw static and dynamic contents of game stats area
    void drawStats(GameEngine *game_engine);

    /// Draw the event text box and its contents
    void drawEventBox();

    /// Add a new event to the event box
    void addEvent(std::string str);

    /// Draw buttons to the game screen
    void drawGameBtns();

    /// Draw tiles, path and towers to game screen
    void drawTiles(GameMap map);

    /// Draw enemies on the path
    void drawEnemies(Enemies enemies);

    /// Poll for events in the game screen
    void mouseBtnEventGame(GameEngine *game_engine);

    /// Print a message when game ends
    void endMessage(bool win, bool done);

    /// Poll for mouse clicks in main menu
    int pollMainScreen();

    /// Poll for mouse clicks in game screen
    sf::Vector3f pollGameScreen();

//private:
    /// Game map size in pixels
    sf::Vector2f m_mapSize;
    /// Game stats / buttons area size in pixels
    sf::Vector2f m_sideBarSize;
    /// Total window size in pixels
    sf::Vector2f m_windowSize;
    /// Game map tile size in pixels
    sf::Vector2f m_tileSize;

    /// Flags for building and updating
    bool m_buildFlag;
    bool m_upgFlag;

    /// App window in which everything is drawn
    sf::RenderWindow &m_window;
    /// Current screen - Main menu or Game
    Screens m_currentScreen;

    /// Lists of buttons in menu and in game screen
    std::vector<graphicsButton> m_menuBtns;
    std::vector<graphicsButton> m_gameBtns;

    /// List of events that occurred in game
    std::deque<std::string> m_gameEvents;
};


#endif