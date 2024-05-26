#ifndef PAGE_HPP
#define PAGE_HPP

#include <SFML/Graphics.hpp>
#include <type_traits>
#include "../widgets/messenger.hpp"

namespace ShareMe
{
    class PageManager;
    
    class Page : public sf::Drawable
    {
    protected:
        Page(PageManager& manager, Messenger& messager);
    public:
        virtual void on_window_resize(const sf::RenderWindow& window);
        virtual void on_hover_items(const sf::RenderWindow& window);
        virtual void on_click_items(const sf::RenderWindow& window);
        virtual void on_event_click_items(const sf::RenderWindow& window);
        virtual void on_right_click_items(const sf::RenderWindow& window);
        virtual void on_text_entered(uint32_t character);
        virtual void on_key_pressed(sf::Keyboard::Key key);
        virtual void draw_render_texture();
        virtual void animation_update();
    public:
        template <typename T>
        static T* As(Page* page)
        {
            static_assert(std::is_base_of<Page, T>::value, "T must be derived from Page");
            return dynamic_cast<T*>(page);
        }
    protected:
        PageManager& pageManager;
        Messenger& messenger;
    };
}

#endif