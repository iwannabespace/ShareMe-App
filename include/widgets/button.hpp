#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "../../external/Cornered/RoundRect.hpp"
#include "../utils/theme.hpp"

namespace ShareMe
{
    class Button : public sf::Drawable
    {
    private:
        using Callback = std::function<void()>;
    public:
        Button(sf::Font& font, const std::string& str, float borderRadius = 6,
            sf::Vector2f size = { 0, 0 }, sf::Vector2f position = { 0, 0 },
            sf::Color color = Theme::PrimaryContainer, 
            sf::Color borderColor = Theme::OnPrimaryContainer, 
            sf::Color textColor = Theme::OnPrimaryContainer);
        ~Button();
        void on_hover(const sf::RenderWindow& window);
        void on_click(const sf::RenderWindow& window);
        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setColor(sf::Color color);
        void setBorderColor(sf::Color color);
        void setTextColor(sf::Color color);
        void setCallback(const Callback& callback);
        void setText(const std::string& text);
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        crd::RoundRect body;
        sf::Text text;
        sf::Color outlineColor;
        Callback callback;
        bool callbackSet = false;
    };
}

#endif