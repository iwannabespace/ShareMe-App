#include "../../include/pages/home_page.hpp"
#include "../../include/utils/theme.hpp"

namespace ShareMe
{
    HomePage::HomePage(sf::Vector2f winSize, sf::Font& primaryFont, sf::Font& secondaryFont, PageManager& pageManager, Messenger& messenger)
        : Page(pageManager, messenger),
          primaryFont(primaryFont),
          secondaryFont(secondaryFont)
    {
        text.setFont(primaryFont);
        text.setCharacterSize(26);
        text.setFillColor(Theme::OnBackground);
        text.setString("No User ID");
        text.setPosition({ 100, 100 });
    }

    HomePage::~HomePage()
    {
    }

    void HomePage::on_window_resize(const sf::RenderWindow& window)
    {
    }

    void HomePage::on_hover_items(const sf::RenderWindow& window)
    {

    }

    void HomePage::on_click_items(const sf::RenderWindow& window)
    {

    }

    void HomePage::on_event_click_items(const sf::RenderWindow& window)
    {

    }

    void HomePage::on_right_click_items(const sf::RenderWindow& window)
    {

    }

    void HomePage::on_text_entered(uint32_t character)
    {

    }

    void HomePage::on_key_pressed(sf::Keyboard::Key key)
    {

    }

    void HomePage::draw_render_texture()
    {

    }

    void HomePage::animation_update()
    {
    }

    void HomePage::setUserId(const std::string& userId)
    {
        this->userId = userId;
        text.setString(userId);
    }

    void HomePage::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(text, states);
    }
}