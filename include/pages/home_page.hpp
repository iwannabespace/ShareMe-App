#ifndef HOME_PAGE_HPP
#define HOME_PAGE_HPP

#include "page.hpp"
#include <string>

namespace ShareMe
{
    class HomePage : public Page
    {
    public:
        HomePage(sf::Vector2f winSize, sf::Font& primaryFont, sf::Font& secondaryFont, PageManager& pageManager, Messenger& messenger);
        ~HomePage();
        void on_window_resize(const sf::RenderWindow& window) override;
        void on_hover_items(const sf::RenderWindow& window) override;
        void on_click_items(const sf::RenderWindow& window) override;
        void on_event_click_items(const sf::RenderWindow& window) override;
        void on_right_click_items(const sf::RenderWindow& window) override;
        void on_text_entered(uint32_t character) override;
        void on_key_pressed(sf::Keyboard::Key key) override;
        void draw_render_texture() override;
        void animation_update() override;
        void setUserId(const std::string& userId);
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Text text;
        sf::Font& primaryFont;
        sf::Font& secondaryFont;
        std::string userId;
    };
}

#endif