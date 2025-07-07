#include "../../include/widgets/link_text.hpp"

namespace ShareMe
{
    LinkText::LinkText(sf::Font& font)
        : font(font), text(font)
    {
    }

    LinkText::LinkText(sf::Font& font, const std::string& str)
        : font(font), text(font, str)
    {
    }

    LinkText::~LinkText()
    {
    }

    void LinkText::on_hover(const sf::RenderWindow& window)
    {   
        if (text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
            text.setStyle(sf::Text::Underlined);
        
        else
            text.setStyle(sf::Text::Regular);
    }

    void LinkText::on_click(const sf::RenderWindow& window)
    {
        if (text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
            if (callbackSet)
                callback();
    }   

    void LinkText::setString(const std::string& str)
    {
        text.setString(str);
    }

    void LinkText::setPosition(sf::Vector2f position)
    {
        text.setPosition(position);
    }

    void LinkText::setCharacsetSize(unsigned int size)
    {
        text.setCharacterSize(size);
    }

    void LinkText::setColor(sf::Color color)
    {
        text.setFillColor(color);
    }

    void LinkText::setCallback(const Callback& callback)
    {
        this->callback = callback;
        callbackSet = true;
    }

    sf::FloatRect LinkText::getGlobalBounds() const
    {
        return text.getGlobalBounds();
    }

    void LinkText::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(text, states);
    }
}