#ifndef COMMON_HPP
#define COMMON_HPP

#include "../pages/page.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace ShareMe
{
    namespace Functions
    {
        void FitText(sf::Text& text, sf::Vector2f size);
        float GetMiddle(float object, float container, float start, float minus);
        float GetTextMaxHeight(const sf::Text& text);
    }
}

#endif