#ifndef TOWER_DEFENCE_2_GRAPHICS_BUTTON_H
#define TOWER_DEFENCE_2_GRAPHICS_BUTTON_H

#include <SFML/Graphics.hpp>
#include "string"


class graphicsButton{
public:

	graphicsButton(sf::Vector2f location, sf::Vector2f size, 
		std::string text);

	sf::Vector2f m_location;
	sf::Vector2f m_size;
	std::string  m_text;
};


#endif