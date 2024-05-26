#ifndef LOADING_ANIMATON_HPP
#define LOADING_ANIMATON_HPP

#include "animation.hpp"

namespace ShareMe
{
    class LoadingAnimation : public Animation
    {
    public:
        LoadingAnimation();
        ~LoadingAnimation();
        void update(float milliseconds) override;
        void setColor(sf::Color color) override;
        void setPosition(sf::Vector2f position) override;
        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        sf::Text text;
        sf::Font font;
        int firstValue = 57426;
        int lastValue = 57541;
        int currentValue = 57426;
    };
}

#endif