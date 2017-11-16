#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>   // For rand()


// This is a test-level code for SFML C++ graphics.
// On linux install SFML as: sudo apt-get install libsfml-dev
// Then compile the code as: g++ -c graphicsTest.cpp; 
//		g++ graphicsTest.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// And run as: ./sfml-app

int main()
{
        // define the sizes of different areas
    sf::Vector2f mapSize(600.f, 600.f);
    sf::Vector2f sidebarSize(200.f, mapSize.y);
    sf::Vector2f windowSize(mapSize.x + sidebarSize.x, mapSize.y);

// ------------------------------------------------------ //

		// Create a window where stuff is drawn - 4:3 aspect ratio
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y,
                                          3), "Graphics test");
    
    	// Store all of the drawables to a vector 
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


// ------------------------------------------------------ //

        // Make tiles on the basis of map size

    int tileAmount = 10; // Assume square map with even number of tiles
    sf::Vector2f tileSize(mapSize.x / tileAmount, mapSize.y / tileAmount);

 		// Colour the tiles according to map info

    // Create a random map
    int randomMap[tileAmount][tileAmount];
    for (int i = 0; i < tileAmount; ++i) {
        for (int j = 0; j < tileAmount; ++j) {
            randomMap[i][j] = rand() % 3; // Values[0,1,2]
            std::cout << randomMap[i][j] << ' ';
        }
        std::cout << std::endl;
    }

// ------------------------------------------------------ //
	    // Draw (and update) the objects to the screen
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
  
  			// Iterate through drawables and draw them on screen
  			// 	OBS: DRAWING HAPPENS IN THE ORDER THEY ARE DEFINED!
  		std::vector<sf::Drawable *>::iterator it = drawables.begin();
  		for( ; it != drawables.end(); it++ )
  		{
  			window.draw(**it);
  		}

            // Iterate through randomMap and draw tiles
        for (int i = 0; i < tileAmount; ++i) {
            for (int j = 0; j < tileAmount; ++j) {
                sf::RectangleShape tmpTile(tileSize);
                tmpTile.setPosition(j*tileSize.x, i*tileSize.y); // OBS j,i !
                tmpTile.setOutlineColor(sf::Color::White);
                tmpTile.setOutlineThickness(2);

                switch(randomMap[i][j])
                {
                    case 0: tmpTile.setFillColor(sf::Color::Green);
                            break;
                    case 1: tmpTile.setFillColor(sf::Color::White);
                            break;
                    case 2: tmpTile.setFillColor(sf::Color::Red);
                            break;
                }
                window.draw(tmpTile);
//                std::cout << randomMap[i][j] << ' ';
            }
//            std::cout << std::endl;
        }

                
        window.display();
    }

    return 0;
}
