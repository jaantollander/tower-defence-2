
Button::Button(sf::Vector2f location, sf::Vector2f size, std::string &text, sf::Font &font){

    sf::RectangleShape m_buttonBox(size);
        m_buttonBox.setPosition(location);
        m_buttonBox.setFillColor(sf::Color::Green);
        m_buttonBox.setOutlineColor(sf::Color::White);
        m_buttonBox.setOutlineThickness(5);

    sf::Text m_buttonText(text, font, 34);
        m_buttonText.setColor(sf::Color::White);
        m_buttonText.setStyle(sf::Text::Bold);
        m_buttonText.setPosition(location * (float) 1.2);


}
