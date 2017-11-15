#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


// This is a test-level code for SFML C++ graphics.
// On linux install SFML as: sudo apt-get install libsfml-dev
// Then compile the code as: g++ -c graphicsTest.cpp; 
//		g++ graphicsTest.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// And run as: ./sfml-app

int main()
{
		// Create a window where stuff is drawn - 4:3 aspect ratio
    sf::RenderWindow window(sf::VideoMode(800, 600,30), "Graphics test");
    
    	// Store all of the drawables to a vector 
    std::vector<sf::Drawable *> drawables;

    	// Create two rectangles for the basis of map and status parts
    sf::RectangleShape mapArea(sf::Vector2f(600.f,600.f)); // Map
    	mapArea.setFillColor(sf::Color::Green);
		mapArea.setOutlineColor(sf::Color::Black);
		mapArea.setOutlineThickness(5);
	drawables.push_back(&mapArea);

    sf::RectangleShape statsArea(sf::Vector2f(200.f,600.f)); // Stats
    	statsArea.setPosition(600,0);
    	statsArea.setFillColor(sf::Color(200,200,200));	// Light gray
		statsArea.setOutlineColor(sf::Color::White);
		statsArea.setOutlineThickness(5);
	drawables.push_back(&statsArea);
		
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


 		// TODO: Make tiles on the basis of map size
 		// TODO: Colour the tiles according to map info


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
                
        window.display();
    }

    return 0;
}
