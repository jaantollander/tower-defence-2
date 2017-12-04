#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>     // For rand()
#include <math.h>       // For round()
#include <string>
#include <iostream>
#include <sstream>


#include "graphicsFunctions.h"
#include "graphicsEngine.h"

#include "graphicsFunctions.cpp"
#include "graphicsEngine.cpp"

// This is a test-level code for SFML C++ graphics.
// On linux install SFML as: sudo apt-get install libsfml-dev
// Then compile the code as: g++ -c graphicsTest.cpp; 
//		g++ graphicsTest.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// And run as: ./sfml-app

int main()
{
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
    std::vector<sf::Vector2f> menuBtns = createAndDrawMenu(window, windowSize);
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
                break;
            }
            case gameScreen:
            {
                    // Window has to be cleaned every time to avoid overlap
                window.clear();
                // Let's draw the window and sidebar
                gameBtns = createAndDrawGame(window, mapSize, sidebarSize);
                    // Let's draw the tiles on the window
                drawTiles(window, randomMap, tileAmount, tileSize);
                    // Let's draw the creatures
                drawCreatures(window, creatures, tileSize);
                    // Let's show stats
                drawStats(window, dummyScore);
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

