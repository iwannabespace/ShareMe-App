#include "../include/app.hpp"
#include "../include/utils/theme.hpp"
#include "../include/managers/font_manager.hpp"
#include "../include/managers/page_manager.hpp"
#include "../include/widgets/link_text.hpp"
#include "../include/pages/login_page.hpp"
#include "../include/pages/register_page.hpp"
#include "../include/pages/home_page.hpp"
#include "../include/utils/functions.hpp"
#include "../include/pages/page.hpp"
#include "../include/widgets/messenger.hpp"
#include "../include/utils/constants.hpp"

#include <iostream>
#include <format>

namespace ShareMe
{ 
    App::App(sf::Vector2f size)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        window.create(sf::VideoMode(size.x, size.y), "ShareMe", sf::Style::Close, settings);
        window.setVerticalSyncEnabled(true);
    }
    
    App::~App()
    {
    }

    bool App::run()
    {
        sf::Vector2f winSize(window.getSize());

        FontManager fontManager;
        fontManager.load("fonts/SpaceMono/SpaceMono-Regular.ttf", "space-mono-regular");
        fontManager.load("fonts/CourierPrime/CourierPrime-Regular.ttf", "courier-prime-regular");

        sf::Font& spaceMonoRegular = *fontManager.get("space-mono-regular").value();
        sf::Font& courierPrimeRegular = *fontManager.get("courier-prime-regular").value();

        Messenger messenger(winSize, courierPrimeRegular);
        SocketClient client(Constants::socketServerUrl, Constants::socketServerPort);

        PageManager pageManager;
        pageManager.addPage(std::make_pair(new LoginPage(winSize, spaceMonoRegular, courierPrimeRegular, pageManager, messenger, client), PageType::Login));
        pageManager.addPage(std::make_pair(new RegisterPage(winSize, spaceMonoRegular, courierPrimeRegular, pageManager, messenger, client), PageType::Register));
        pageManager.addPage(std::make_pair(new HomePage(winSize, spaceMonoRegular, courierPrimeRegular, pageManager, messenger, client), PageType::Home));

        sf::Clock clock;

        if (!client.connect())
        {
            std::cout << "Connection so socket client failed!" << std::endl;
        }

        while (window.isOpen())
        {
            auto activePageData = pageManager.getActivePage();
            auto activePage = activePageData.first;
            sf::Event event;

            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    break;
                case sf::Event::MouseButtonReleased:
                    activePage->on_event_click_items(window);
                    break;
                case sf::Event::MouseWheelScrolled:
                    break;
                case sf::Event::TextEntered:
                    activePage->on_text_entered(event.text.unicode);
                    break;
                case sf::Event::KeyPressed:
                    activePage->on_key_pressed(event.key.code);
                    break;
                default:
                    break;
                }
            }

            float deltaTime = clock.getElapsedTime().asSeconds();

            activePage->on_hover_items(window);
            activePage->on_click_items(window);
            activePage->draw_render_texture();
            activePage->animation_update();

            if (activePageData.second == PageType::Login) {
                LoginPage* asLogin = Page::As<LoginPage>(activePage);
                asLogin->on_login();
            } else if (activePageData.second == PageType::Register) {
                RegisterPage* asRegister =  Page::As<RegisterPage>(activePage);
                asRegister->on_register();
                asRegister->on_verify();
            } else {
                //HomePage* asHome = Page::As<HomePage>(activePage);
            }

            messenger.update();

            window.clear(Theme::Background);
            window.draw(*activePage);
            window.draw(messenger);
            window.display();

            clock.restart();
        }

        return true;
    }
}