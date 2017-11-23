
class Button{
public:
    //sf::Vector2i m_location;
    //sf::Vector2i m_size;

    //sf::Color m_buttonColor;

    sf::RectangleShape m_buttonBox;
    sf::Text  m_buttonText;

    Button(sf::Vector2f location, sf::Vector2f size, std::string &text, sf::Font &font);
};