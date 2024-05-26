#ifndef LINK_TEXT_HPP
#define LINK_TEXT_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include "../utils/theme.hpp"

namespace ShareMe
{
    class LinkText : public sf::Drawable
    {
    private:
        using Callback = std::function<void()>;
    public:
        LinkText(sf::Font &font);
        LinkText(sf::Font &font, const std::string &str);
        ~LinkText();
        void on_hover(const sf::RenderWindow &window);
        void on_click(const sf::RenderWindow &window);
        void setString(const std::string &str);
        void setPosition(sf::Vector2f position);
        void setCharacsetSize(unsigned int size);
        void setColor(sf::Color color);
        void setCallback(const Callback &callback);
        sf::FloatRect getGlobalBounds() const;
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        sf::Text text;
        sf::Font &font;
        Callback callback;
        bool callbackSet = false;
    };
}

#endif