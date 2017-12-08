#include "graphicsButton.h"
#include <SFML/Graphics.hpp>

graphicsButton::graphicsButton(sf::Vector2f location, sf::Vector2f size,
	 std::string text):m_location(location), m_size(size), m_text(text) {};
