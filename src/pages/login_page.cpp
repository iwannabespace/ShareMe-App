#include "../../include/pages/login_page.hpp"
#include "../../include/pages/home_page.hpp"
#include "../../include/utils/functions.hpp"
#include "../../include/utils/theme.hpp"
#include "../../include/utils/validator.hpp"
#include <iostream>

namespace ShareMe
{
    LoginPage::LoginPage(sf::Vector2f winSize, sf::Font& primaryFont, sf::Font& secondaryFont, PageManager& pageManager, Messenger& messenger, SocketClient& client)
        : Page(pageManager, messenger, client),
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
        description.setString("Share your thoughts with us!");
        description.setCharacterSize(16);
        description.setFillColor(Theme::OnBackground);
        description.setStyle(sf::Text::Italic);
        description.setPosition({
            textboxPositionX,
            title.getPosition().y + title.getGlobalBounds().height + 20
        });

        registerLink.setCallback([&pageManager = this->pageManager]() {
            pageManager.switchTo(PageType::Register);
        });

        loginButton.setCallback([&]() { 
            bool result = client.send({ 7, 100 });
            
            std::cout << std::boolalpha << std::endl;

            handle_login(); 
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
        if (gettingSalt)
        {
            if (getSaltFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
            {
                auto getSaltResult = getSaltFuture.get();
                auto apiResult = getSaltResult.result;
                auto params = ApiResultHandler::MessageParams();
                auto onSuccess = [this, &getSaltResult]() {
                    std::string password = passwordTextbox.value();
                    std::string salt = getSaltResult.salt;
                    std::string sha256 = Functions::SHA256(password + salt);

                    loginFuture = Api::Login(emailTextbox.value(), sha256);
                    signing = true;
                };
                auto onFailure = [&showLoadingAnimation = showLoadingAnimation]() { showLoadingAnimation = false; };
                gettingSalt = false;

                ApiResultHandler::Handle(apiResult, messenger, params, onSuccess, onFailure);
            }
        }

        else if (signing)
        {
            if (loginFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
            {
                auto loginResult = loginFuture.get();
                auto apiResult = loginResult.result;
                auto params = ApiResultHandler::MessageParams();
                auto onSuccess = [this, &loginResult]() {
                    auto pageData = pageManager.getPage(PageType::Home);
                    HomePage* home = Page::As<HomePage>(pageData.first);
                    home->setAuthData(loginResult.authData);
                    pageManager.switchTo(PageType::Home);
                    Functions::SaveTokens(loginResult.authData);
                };
                signing = false;
                showLoadingAnimation = false;

                ApiResultHandler::Handle(apiResult, messenger, params, onSuccess);
            }
        }
    }

    void LoginPage::handle_login()
    {
        std::string email = emailTextbox.value();
        std::string password = passwordTextbox.value();

        Validator::Result emailValidationResult = Validator::ValidateEmail(email);
        Validator::Result passwordValidationResult = Validator::ValidatePassword(password);

        if (emailValidationResult == Validator::Result::Success && passwordValidationResult == Validator::Result::Success) {
            getSaltFuture = Api::GetSalt(email);
            gettingSalt = true;
            showLoadingAnimation = true;
        } else {
            if (emailValidationResult != Validator::Result::Success) {
                std::string errorMessage = Validator::GetErrorMessage(emailValidationResult);
                messenger.addMessage(errorMessage);
                emailTextbox.enableError(errorMessage);
            } else if (passwordValidationResult != Validator::Result::Success) {
                std::string errorMessage = Validator::GetErrorMessage(passwordValidationResult);
                messenger.addMessage(errorMessage);
                passwordTextbox.enableError(errorMessage);
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