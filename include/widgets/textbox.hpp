#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include "../../external/Cornered/RoundRect.hpp"
#include "../utils/theme.hpp"

namespace ShareMe
{
    class Textbox : public sf::Drawable
    {
    public:
        Textbox(sf::Font& font, const sf::String& placeholder, 
            sf::Vector2f size = { 0, 0 }, sf::Vector2f position = { 0, 0 }, 
            float borderRadius = 6, float border_width = 1.f, std::optional<size_t> maxCharacter = std::nullopt, 
            const std::string& def = "", bool numberOnly = false,
            sf::Color color = Theme::PrimaryContainer, 
            sf::Color hovered_color = Theme::OnPrimaryContainer, sf::Color focused_color = Theme::OnPrimaryContainer, 
            sf::Color text_color = Theme::OnPrimaryContainer, sf::Color placeholder_color = Theme::OnPrimary);
        ~Textbox();
        void on_input(uint32_t character);
        void on_shortcuts();
        void on_text_left();
        void on_text_right();
        void on_hover(const sf::RenderWindow& window);
        void on_click(const sf::RenderWindow& window);
        void draw_rt();
        void clear();
        void enable();
        void disable();
        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setBorderRadius(float radius);
        void setColor(sf::Color color);
        void setHoveredColor(sf::Color color);
        void setFocusedColor(sf::Color color);
        void setTextColor(sf::Color color);
        void setPlaceholderColor(sf::Color color);
        void enableError(const std::string& errorMessage);
        void disableError();
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        std::string value() const;
        bool active() const;
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool is_number(const std::string& str) const;
    private:
        sf::RenderTexture renderer;
        crd::RoundRect container;
        sf::RectangleShape cover;
        sf::Text text;
        sf::Text placeholder_text;
        sf::Text errorText;
        sf::String string;
        sf::String placeholder_str;
        sf::Font& font;
        sf::Color color, colorCopy;
        sf::Color hovered_color;
        sf::Color focused_color;
        sf::Color enabled_color;
        sf::Vector2f text_pos;
        size_t cursor_index;
        std::optional<size_t> maxCharacter;
        float oneCharWidth;
        float oneCharHeight;
        bool focused;
        bool selected;
        bool enabled = true;
        bool numberOnly = false;
        bool showError = false;
    };
}

#endif