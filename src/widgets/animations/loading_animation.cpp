#include "../../../include/widgets/animations/loading_animation.hpp"
#include <string>

namespace ShareMe
{
    LoadingAnimation::LoadingAnimation()
        : text(font)
    {
        font.openFromFile("fonts/meiryo_boot.ttf");
        std::wstring str;
        str += currentValue;
        text.setString(str);
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::White);
    }

    LoadingAnimation::~LoadingAnimation()
    {
    }

    void LoadingAnimation::update(float milliseconds)
    {
        if (clock.getElapsedTime().asMilliseconds() >= milliseconds)
        {
            if (currentValue <= lastValue)
            {
                currentValue++;
                std::wstring str;
                str += currentValue;
                text.setString(str);
            }

            else
            {
                currentValue = firstValue;
                std::wstring str;
                str += currentValue;
                text.setString(str);
            }

            clock.restart();
        }
    }

    void LoadingAnimation::setColor(sf::Color color)
    {
        text.setFillColor(color);
    }

    void LoadingAnimation::setPosition(sf::Vector2f position)
    {
        text.setPosition(position);
    }

    sf::FloatRect LoadingAnimation::getLocalBounds() const
    {
        return text.getLocalBounds();;
    }

    sf::FloatRect LoadingAnimation::getGlobalBounds() const
    {
        return text.getGlobalBounds();
    }

    void LoadingAnimation::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(text, states);
    }
}