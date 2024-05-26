#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

namespace ShareMe
{
    class Animation : public sf::Drawable
    {
    public:
        virtual void update(float milliseconds) = 0;
        virtual void setColor(sf::Color color) = 0;
        virtual void setPosition(sf::Vector2f position) = 0;
    protected:
        sf::Clock clock;
    };
}

#endif