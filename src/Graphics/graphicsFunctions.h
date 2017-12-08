#ifndef TOWER_DEFENCE_2_GRAPHICS_FUNCTIONS_H
#define TOWER_DEFENCE_2_GRAPHICS_FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>     // For rand()
#include <cmath>       // For round()
#include <string>
#include <iostream>
#include <sstream>

enum Screens
{
    mainScreen,
    gameScreen
};

std::vector<sf::Vector2f> createAndDrawMenu(sf::RenderWindow &window,
                            sf::Vector2f windowSize);

void createAndDrawButton(sf::RenderWindow &window, sf::Vector2f buttonLU, sf::Vector2f buttonSize,
                         std::string &text, sf::Font &font);

std::vector<sf::Vector2f> createAndDrawGame(sf::RenderWindow &window,
                            sf::Vector2f mapSize, sf::Vector2f sidebarSize);



void drawDrawables(sf::RenderWindow &window,
                   std::vector<sf::Drawable *> drawables);

void drawTiles(sf::RenderWindow &window, std::vector< std::vector<int> > &map,
               int tileAmount, sf::Vector2f tileSize);

void drawCreatures(sf::RenderWindow &window,
                   std::vector<sf::Vector3f> creatures, sf::Vector2f tileSize);

Screens mainScreenPoller(sf::RenderWindow &window, sf::Vector2f windowSize);

sf::Vector2f gameScreenPoller(sf::RenderWindow &window,
                                           std::vector<sf::Vector3f> &creatures,
                                           std::vector<sf::Vector2f> gameBtns);

void drawStats(sf::RenderWindow &window, int stats);

#endif