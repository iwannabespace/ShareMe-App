#include "../../include/pages/login_page.hpp"
#include "../../include/pages/home_page.hpp"
#include "../../include/utils/functions.hpp"
#include "../../include/utils/theme.hpp"
#include <iostream>

namespace ShareMe
{
    LoginPage::LoginPage(sf::Vector2f winSize, sf::Font& primaryFont, sf::Font& secondaryFont, PageManager& pageManager, Messenger& messenger)
        : Page(pageManager, messenger),
          emailTextbox(secondaryFont, "Email"),
          passwordTextbox(secondaryFont, "Password"),
          loginButton(secondaryFont, "Login", 8),
          registerLink(secondaryFont),
          primaryFont(primaryFont), 
          secondaryFont(secondaryFont)
    {
        float width = winSize.x;
        float height = winSize.y;
        float textboxWidth = width - 100;
        float textboxHeight = 40;
        float buttonWidth = 210;
        float buttonHeight = 30;
        float textboxPositionX = Functions::GetMiddle(textboxWidth, width, 0, 0);

        emailTextbox.setSize({textboxWidth, textboxHeight});
        emailTextbox.setPosition({textboxPositionX, 300});

        passwordTextbox.setSize({textboxWidth, textboxHeight});
        passwordTextbox.setPosition({
            textboxPositionX,
            emailTextbox.getPosition().y + textboxHeight + 20
        });

        loginButton.setSize({buttonWidth, buttonHeight});
        loginButton.setPosition({
            Functions::GetMiddle(buttonWidth, width, 0, 0), 
            passwordTextbox.getPosition().y + textboxHeight + 20
        });

        registerLink.setCharacsetSize(12);
        registerLink.setColor(Theme::OnBackground);
        registerLink.setString("You don't have an account? Register here!");
        registerLink.setPosition({
            Functions::GetMiddle(registerLink.getGlobalBounds().width, width, 0, 0), 
            height - registerLink.getGlobalBounds().height - 75
        });

        loadingAnimation.setColor(Theme::OnBackground);
        loadingAnimation.setPosition({
            Functions::GetMiddle(loadingAnimation.getGlobalBounds().width, width, 0, loadingAnimation.getGlobalBounds().left) - 15,
            loginButton.getPosition().y + loginButton.getSize().y + 50,
        });

        title.setFont(primaryFont);
        title.setString("Login");
        title.setCharacterSize(32);
        title.setFillColor(Theme::OnBackground);
        title.setStyle(sf::Text::Bold);
        title.setPosition({
            emailTextbox.getPosition().x,
            emailTextbox.getPosition().y - 150
        });

        description.setFont(primaryFont);
        description.setString("Share your thoughts wiht us!");
        description.setCharacterSize(16);
        description.setFillColor(Theme::OnBackground);
        description.setStyle(sf::Text::Italic);
        description.setPosition({
            textboxPositionX,
            title.getPosition().y + title.getGlobalBounds().height + 20
        });

        registerLink.setCallback([this]() {
            this->pageManager.switchTo(PageType::Register);
        });

        loginButton.setCallback([this]() {
            std::string email = this->emailTextbox.value();
            std::string password = this->passwordTextbox.value();
            if (!email.empty() && !password.empty()) {
                this->loginFuture = Api::Login(email, password);
                this->signing = true;
                this->showLoadingAnimation = true;
            } else {
                this->messenger.addMessage("All fields are required");
            }
        });
    }

    LoginPage::~LoginPage()
    {
    }

    void LoginPage::on_window_resize(const sf::RenderWindow &window)
    {
    }

    void LoginPage::on_hover_items(const sf::RenderWindow &window)
    {
        emailTextbox.on_hover(window);
        passwordTextbox.on_hover(window);
        loginButton.on_hover(window);
        registerLink.on_hover(window);
    }

    void LoginPage::on_click_items(const sf::RenderWindow &window)
    {
        emailTextbox.on_click(window);
        passwordTextbox.on_click(window);
    }

    void LoginPage::on_event_click_items(const sf::RenderWindow &window)
    {
        loginButton.on_click(window);
        registerLink.on_click(window);
    }

    void LoginPage::on_right_click_items(const sf::RenderWindow &window)
    {
    }

    void LoginPage::on_text_entered(uint32_t character)
    {
        emailTextbox.on_input(character);
        passwordTextbox.on_input(character);
    }

    void LoginPage::on_key_pressed(sf::Keyboard::Key key)
    {
        emailTextbox.on_shortcuts();
        passwordTextbox.on_shortcuts();

        if (key == sf::Keyboard::Key::Left)
        {
            if (emailTextbox.active()) { emailTextbox.on_text_left(); }
            if (passwordTextbox.active()) { passwordTextbox.on_text_left(); }
        }

        else if (key == sf::Keyboard::Key::Right)
        {
            if (emailTextbox.active()) { emailTextbox.on_text_right(); }
            if (passwordTextbox.active()) { passwordTextbox.on_text_right(); }
        }
    }

    void LoginPage::draw_render_texture()
    {
        emailTextbox.draw_rt();
        passwordTextbox.draw_rt();
    }

    void LoginPage::animation_update()
    {
        if (showLoadingAnimation)
        {
            loadingAnimation.update(20);
        }
    }

    void LoginPage::on_login()
    {
        if (signing)
        {
            if (loginFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
            {
                auto loginResult = loginFuture.get();
                auto apiResult = loginResult.result;
                std::cout << apiResult << std::endl;
                switch (apiResult) {
                    case ApiResult::Success:
                    {    
                        auto pageData = pageManager.getPage(PageType::Home);
                        HomePage* asHome = Page::As<HomePage>(pageData.first);
                        asHome->setUserId(loginResult.userId);
                        pageManager.switchTo(PageType::Home);
                        break;
                    }
                    case ApiResult::UserNotActive:
                        messenger.addMessage("Please activate your account first!");
                        break;
                    case ApiResult::InvalidCredentials:
                        messenger.addMessage("Invalid credentials!");
                        break;
                    case ApiResult::UserNotFound:
                        messenger.addMessage("This email is not registered!");
                        break;
                    case ApiResult::ValidationError:
                        messenger.addMessage("This email is not valid1");
                        break;
                    case ApiResult::ServerError:
                        messenger.addMessage("Server error!");
                        break;
                    case ApiResult::Unreachable:
                        messenger.addMessage("Remote server is unreachable!");
                        break;
                    default:
                        messenger.addMessage("Problem occured!");
                        break;
                }

                signing = false;
                showLoadingAnimation = false;
            }
        }
    }

    void LoginPage::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(title, states);
        target.draw(description, states);
        target.draw(emailTextbox, states);
        target.draw(passwordTextbox, states);
        target.draw(loginButton, states);
        target.draw(registerLink, states);

        if (showLoadingAnimation) target.draw(loadingAnimation, states);
    }
}