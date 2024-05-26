#include "../../include/widgets/button.hpp"
#include "../../include/utils/functions.hpp"

namespace ShareMe
{
    Button::Button(sf::Font& font, const std::string& str, float borderRadius,
            sf::Vector2f size, sf::Vector2f position,
            sf::Color color, 
            sf::Color borderColor, 
            sf::Color textColor)
        : outlineColor(borderColor)
    {
        body.setSize(size);
        body.setPosition(position);
        body.setFillColor(color);
        body.setOutlineColor(sf::Color::Transparent);
        body.setOutlineThickness(1);
        body.setRadius(borderRadius);

        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(12);
        text.setFillColor(textColor);
        text.setPosition({
            Functions::GetMiddle(text.getGlobalBounds().width, size.x, position.x, 0),
            Functions::GetMiddle(text.getGlobalBounds().height, size.y, position.y, text.getGlobalBounds().top),
        });
    }

    Button::~Button()
    {
    }

    void Button::on_hover(const sf::RenderWindow& window)
    {
        if (body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
            body.setOutlineColor(outlineColor);
        
        else
            body.setOutlineColor(sf::Color::Transparent);
    }

    void Button::on_click(const sf::RenderWindow& window)
    {
        if (body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
            if (callbackSet)
                callback();
    }

    void Button::setPosition(sf::Vector2f position)
    {
        body.setPosition(position);
        text.setPosition({
            Functions::GetMiddle(text.getGlobalBounds().width, body.getSize().x, body.getPosition().x, 0),
            Functions::GetMiddle(text.getGlobalBounds().height, body.getSize().y, body.getPosition().y, text.getLocalBounds().top),
        });
    }

    void Button::setSize(sf::Vector2f size)
    {
        body.setSize(size);
        text.setPosition({
            Functions::GetMiddle(text.getGlobalBounds().width, body.getSize().x, body.getPosition().x, 0),
            Functions::GetMiddle(text.getGlobalBounds().height, body.getSize().y, body.getPosition().y, text.getGlobalBounds().top),
        });
    }

    void Button::setColor(sf::Color color)
    {
        body.setFillColor(color);
    }

    void Button::setBorderColor(sf::Color color)
    {
        outlineColor = color;
    }

    void Button::setTextColor(sf::Color color)
    {
        text.setFillColor(color);
    }

    void Button::setText(const std::string& text)
    {   
        this->text.setString(text);
    }

    void Button::setCallback(const Callback& callback)
    {
        this->callback = callback;
        callbackSet = true;
    }

    sf::Vector2f Button::getPosition() const
    {
        return body.getPosition();
    }

    sf::Vector2f Button::getSize() const
    {
        return body.getSize();
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(body, states);
        target.draw(text, states);
    }
}