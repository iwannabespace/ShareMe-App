#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>

namespace ShareMe
{
    class App
    {
    public:
        App(sf::Vector2f size = {500, 700});
        ~App();
        bool run();
    private:
        sf::RenderWindow window;
    };
}

#endif