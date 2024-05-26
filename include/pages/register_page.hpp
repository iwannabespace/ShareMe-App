#ifndef REGISTER_PAGE_HPP
#define REGISTER_PAGE_HPP

#include "page.hpp"
#include "../managers/page_manager.hpp"
#include "../widgets/textbox.hpp"
#include "../widgets/button.hpp"
#include "../widgets/link_text.hpp"
#include "../widgets/animations/loading_animation.hpp"
#include "../api/api.hpp"
#include <future>

namespace ShareMe
{
    class RegisterPage : public Page
    {
    public:
        RegisterPage(sf::Vector2f winSize, sf::Font& primaryFont, sf::Font& secondaryFont, PageManager& pageManager, Messenger& messenger);
        ~RegisterPage();
        void on_window_resize(const sf::RenderWindow& window) override;
        void on_hover_items(const sf::RenderWindow& window) override;
        void on_click_items(const sf::RenderWindow& window) override;
        void on_event_click_items(const sf::RenderWindow& window) override;
        void on_right_click_items(const sf::RenderWindow& window) override;
        void on_text_entered(uint32_t character) override;
        void on_key_pressed(sf::Keyboard::Key key) override;
        void draw_render_texture() override;
        void animation_update() override;
        void on_register();
        void on_verify();
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Text title;
        sf::Text description;
        Textbox emailTextbox;
        Textbox usernameTextbox;
        Textbox passwordTextbox;
        Textbox verificationTextbox;
        Button registerButton;
        LinkText loginLink;
        LoadingAnimation loadingAnimation;
        sf::Font& primaryFont;
        sf::Font& secondaryFont;
        bool registering = false;
        bool verifying = false;
        bool showVerification = false;
        bool showLoadingAnimation = false;
        std::future<ApiResult> registerFuture;
        std::future<ApiResult> verifyFuture;
    };
}

#endif