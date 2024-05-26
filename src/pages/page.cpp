#include "../../include/pages/page.hpp"
#include "../../include/managers/page_manager.hpp"
#include "../../include/widgets/messenger.hpp"
#include "../../include/pages/login_page.hpp"
#include "../../include/pages/register_page.hpp"
#include "../../include/pages/home_page.hpp"

#include <type_traits>

namespace ShareMe
{
    Page::Page(PageManager& manager, Messenger& messenger) : pageManager(manager), messenger(messenger) { }

    void Page::on_window_resize(const sf::RenderWindow& window)
    {

    }

    void Page::on_hover_items(const sf::RenderWindow& window)
    {

    }

    void Page::on_click_items(const sf::RenderWindow& window)
    {

    }

    void Page::on_event_click_items(const sf::RenderWindow& window)
    {

    }

    void Page::on_right_click_items(const sf::RenderWindow& window)
    {

    }

    void Page::on_text_entered(uint32_t character)
    {

    }

    void Page::on_key_pressed(sf::Keyboard::Key key)
    {

    }

    void Page::draw_render_texture()
    {

    }

    void Page::animation_update()
    {

    }
}