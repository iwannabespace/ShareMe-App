#include "../../include/pages/register_page.hpp"
#include "../../include/utils/functions.hpp"
#include "../../include/utils/theme.hpp"
#include "../../include/api/api.hpp"
#include <iostream>
#include <format>
#include <print>

namespace ShareMe
{
    RegisterPage::RegisterPage(sf::Vector2f winSize, sf::Font& primaryFont, sf::Font& secondaryFont, PageManager& pageManager, Messenger& messenger, SocketClient& client)
        : Page(pageManager, messenger, client),
          emailTextbox(secondaryFont, "Email"),
          usernameTextbox(secondaryFont, "Username"),
          passwordTextbox(secondaryFont, "Password"),
          verificationTextbox(secondaryFont, "Verification code", {}, {}, 6, 1, 6),
          registerButton(secondaryFont, "Register", 8),
          loginLink(secondaryFont),
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

        usernameTextbox.setSize({textboxWidth, textboxHeight});
        usernameTextbox.setPosition({
            textboxPositionX, 
            emailTextbox.getPosition().y + textboxHeight + 20
        });

        passwordTextbox.setSize({textboxWidth, textboxHeight});
        passwordTextbox.setPosition({
            textboxPositionX,
            usernameTextbox.getPosition().y + textboxHeight + 20
        });

        verificationTextbox.setSize({textboxWidth, textboxHeight});
        verificationTextbox.setPosition({
            textboxPositionX,
            passwordTextbox.getPosition().y + textboxHeight + 20
        });

        registerButton.setSize({buttonWidth, buttonHeight});
        registerButton.setPosition({
            Functions::GetMiddle(buttonWidth, width, 0, 0), 
            passwordTextbox.getPosition().y + textboxHeight + 20
        });

        loginLink.setCharacsetSize(12);
        loginLink.setColor(Theme::OnBackground);
        loginLink.setString("You already have an account? Login here!");
        loginLink.setPosition({
            Functions::GetMiddle(loginLink.getGlobalBounds().width, width, 0, 0), 
            height - loginLink.getGlobalBounds().height - 75
        });

        loadingAnimation.setColor(Theme::OnBackground);
        loadingAnimation.setPosition({
            Functions::GetMiddle(loadingAnimation.getGlobalBounds().width, width, 0, loadingAnimation.getGlobalBounds().left) - 15,
            registerButton.getPosition().y + registerButton.getSize().y + 50,
        });

        title.setFont(primaryFont);
        title.setString("Register");
        title.setCharacterSize(32);
        title.setFillColor(Theme::OnBackground);
        title.setStyle(sf::Text::Bold);
        title.setPosition({
            textboxPositionX,
            emailTextbox.getPosition().y - 150
        });

        description.setFont(primaryFont);
        description.setString("Become a member of the community!");
        description.setCharacterSize(16);
        description.setFillColor(Theme::OnBackground);
        description.setStyle(sf::Text::Italic);
        description.setPosition({
            textboxPositionX,
            title.getPosition().y + title.getGlobalBounds().height + 20
        });

        loginLink.setCallback([this]() {
            if (!this->registering && !this->verifying) {
                this->registerButton.setPosition({
                    this->registerButton.getPosition().x, 
                    this->passwordTextbox.getPosition().y + this->passwordTextbox.getSize().y + 20
                });
                this->registerButton.setText("Register");
                this->showVerification = false;
                this->pageManager.switchTo(PageType::Login);
            }
        });

        registerButton.setCallback([this]() { this->handle_register(); });
    }

    RegisterPage::~RegisterPage()
    {
    }

    void RegisterPage::on_window_resize(const sf::RenderWindow &window)
    {
    }

    void RegisterPage::on_hover_items(const sf::RenderWindow &window)
    {
        emailTextbox.on_hover(window);
        usernameTextbox.on_hover(window);
        passwordTextbox.on_hover(window);
        registerButton.on_hover(window);
        loginLink.on_hover(window);

        if (showVerification) verificationTextbox.on_hover(window);
    }

    void RegisterPage::on_click_items(const sf::RenderWindow &window)
    {
        emailTextbox.on_click(window);
        usernameTextbox.on_click(window);
        passwordTextbox.on_click(window);

        if (showVerification) verificationTextbox.on_click(window);
    }

    void RegisterPage::on_event_click_items(const sf::RenderWindow &window)
    {
        registerButton.on_click(window);
        loginLink.on_click(window);
    }

    void RegisterPage::on_right_click_items(const sf::RenderWindow &window)
    {
    }

    void RegisterPage::on_text_entered(uint32_t character)
    {
        emailTextbox.on_input(character);
        usernameTextbox.on_input(character);
        passwordTextbox.on_input(character);

        if (showVerification) verificationTextbox.on_input(character);
    }

    void RegisterPage::on_key_pressed(sf::Keyboard::Key key)
    {
        emailTextbox.on_shortcuts();
        usernameTextbox.on_shortcuts();
        passwordTextbox.on_shortcuts();

        if (showVerification) verificationTextbox.on_shortcuts();

        if (key == sf::Keyboard::Key::Left)
        {
            if (emailTextbox.active()) { emailTextbox.on_text_left(); }
            else if (usernameTextbox.active()) { usernameTextbox.on_text_left(); }
            else if (passwordTextbox.active()) { passwordTextbox.on_text_left(); }
        }

        else if (key == sf::Keyboard::Key::Right)
        {
            if (emailTextbox.active()) { emailTextbox.on_text_right(); }
            else if (usernameTextbox.active()) { usernameTextbox.on_text_right(); }
            else if (passwordTextbox.active()) { passwordTextbox.on_text_right(); }

            if (showVerification)
            {
                if (verificationTextbox.active()) { verificationTextbox.on_text_right(); }
            }
        }
    }

    void RegisterPage::draw_render_texture()
    {
        emailTextbox.draw_rt();
        usernameTextbox.draw_rt();
        passwordTextbox.draw_rt();

        if (showVerification) verificationTextbox.draw_rt();
    }

    void RegisterPage::animation_update()
    {
        if (showLoadingAnimation)
        {
            loadingAnimation.update(20);
        }
    }

    void RegisterPage::on_register()
    {
        if (registering)
        {
            if (registerFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
            {
                auto apiResult = registerFuture.get();
                auto params = ApiResultHandler::MessageParams();
                auto onSuccess = [this, &apiResult]() {
                    registerButton.setPosition({
                        registerButton.getPosition().x, 
                        verificationTextbox.getPosition().y + verificationTextbox.getSize().y + 20
                    });
                    registerButton.setText("Verify");
                    showVerification = true;
                };
                
                registering = false;
                showLoadingAnimation = false;

                ApiResultHandler::Handle(apiResult, messenger, params, onSuccess);
            }
        }
    }

    void RegisterPage::on_verify()
    {
        if (verifying)
        {
            if (verifyFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
            {
                auto apiResult = verifyFuture.get();
                auto params = ApiResultHandler::MessageParams();
                auto onSuccess = [this, &apiResult]() {
                    messenger.addMessage("Verification successful!");
                    pageManager.switchTo(PageType::Login);
                    registerButton.setPosition({
                        registerButton.getPosition().x, 
                        passwordTextbox.getPosition().y + passwordTextbox.getSize().y + 20
                    });
                    registerButton.setText("Register");
                    emailTextbox.clear();
                    usernameTextbox.clear();
                    passwordTextbox.clear();
                    verificationTextbox.clear();
                    showVerification = false;
                };
                
                verifying = false;
                showLoadingAnimation = false;

                ApiResultHandler::Handle(apiResult, messenger, params, onSuccess);
            }
        }
    }

    void RegisterPage::handle_register()
    {
        if (!showVerification) {
            auto email = emailTextbox.value();
            auto username = usernameTextbox.value();
            auto password = passwordTextbox.value();

            if (!email.empty() && !username.empty() && !password.empty()) {
                std::string salt = Functions::GenerateSalt(16);
                std::string sha256 = Functions::SHA256(password + salt);
                registerFuture = Api::Register(email, username, sha256, salt);
                registering = true;
                showLoadingAnimation = true;   
            } else {
                messenger.addMessage("All fields are required!");
            }
        } else {
            std::string code = verificationTextbox.value();
            if (code.length() == 6) {
                verifyFuture = Api::Verify(code);
                verifying = true;
                showLoadingAnimation = true;
            } else {
                messenger.addMessage("Verification code must be 6 digits long!");
            }
        }
    }

    void RegisterPage::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(title, states);
        target.draw(description, states);
        target.draw(emailTextbox, states);
        target.draw(usernameTextbox, states);
        target.draw(passwordTextbox, states);
        target.draw(registerButton, states);
        target.draw(loginLink, states);
        
        if (showVerification) target.draw(verificationTextbox, states);
        if (showLoadingAnimation) target.draw(loadingAnimation, states);
    }
}