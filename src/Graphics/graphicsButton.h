class graphicsButton{
public:

	graphicsButton(sf::Vector2f location, sf::Vector2f size, 
		std::string text);

	sf::Vector2f m_location;
	sf::Vector2f m_size;
	std::string  m_text;
};
