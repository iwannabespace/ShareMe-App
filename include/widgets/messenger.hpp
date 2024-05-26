#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include <chrono>

namespace ShareMe
{
    struct Message
    {
        std::string message;
        int32_t duration;
        std::chrono::steady_clock::time_point start;
    };

    class Messenger : public sf::Drawable
    {
    public:
        Messenger(sf::Vector2f winSize, sf::Font& font);
        ~Messenger();
        void on_window_resize(const sf::RenderWindow& window);
        void addMessage(const std::string& message, int32_t duration = 3000);
        void update(float deltaTime);
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        std::queue<Message> messages;
        sf::RectangleShape container;
        sf::Text text;
        sf::Font& font;
        bool animationShowStart = false;
        bool animationEndStart = false;
        float intendedShowYPosition = 0;
        float intendedEndYPosition = 0;
        float animationSpeed = 10000;
    };
}

#endif