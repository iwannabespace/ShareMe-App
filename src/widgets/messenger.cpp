#include "../../include/widgets/messenger.hpp"
#include "../../include/utils/theme.hpp"
#include "../../include/utils/functions.hpp"
#include <iostream>

namespace ShareMe
{
    Messenger::Messenger(sf::Vector2f winSize, sf::Font& font)
        : font(font)
    {
        float containerHeight = 35;
        container.setSize({ winSize.x, containerHeight });
        container.setFillColor(Theme::PrimaryContainer);
        container.setPosition({ 0, winSize.y });

        text.setFont(font);
        text.setCharacterSize(12);
        text.setFillColor(Theme::OnPrimaryContainer);

        text.setPosition({
            20,
            Functions::GetMiddle(Functions::GetTextMaxHeight(text), containerHeight, container.getPosition().y, 0)
        });

        intendedShowYPosition = winSize.y - containerHeight;
        intendedEndYPosition = winSize.y;
    }

    Messenger::~Messenger()
    {
    }

    void Messenger::on_window_resize(const sf::RenderWindow& window)
    {
    }

    void Messenger::addMessage(const std::string& message, int32_t duration)
    {
        if (messages.empty())
        {    
            text.setString(message);
            animationShowStart = true;
            animationEndStart = false;
        }
        
        auto now = std::chrono::high_resolution_clock::now();

        messages.push({ message, duration, now });
    }

    void Messenger::update(float deltaTime)
    {
        if (animationShowStart) {
            float containerY = container.getPosition().y;
            if (containerY > intendedShowYPosition) {
                container.move({ 0, -(animationSpeed * deltaTime)});
                text.move({ 0, -(animationSpeed * deltaTime) });
            } else {
                animationShowStart = false;
            }
        } else if (!animationShowStart && !animationEndStart) {
            if (!messages.empty())
            {
                Message& message = messages.front();

                auto now = std::chrono::high_resolution_clock::now();
                auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - message.start);

                if (diff.count() >= message.duration)
                {
                    messages.pop();
                    if (!messages.empty()) {
                        Message& nextMessage = messages.front();
                        std::cout << "Next message: " << nextMessage.message << std::endl;
                        nextMessage.start = std::chrono::high_resolution_clock::now();
                        text.setString(nextMessage.message);
                    } else {
                        animationEndStart = true;
                    }
                }
            }
        } else if (animationEndStart) {
            float containerY = container.getPosition().y;
            if (containerY < intendedEndYPosition) {
                container.move({ 0, animationSpeed * deltaTime });
                text.move({ 0, animationSpeed * deltaTime });
            } else {
                animationEndStart = false;
            }
        }
    }   

    void Messenger::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if (!messages.empty() || animationEndStart)
        {
            target.draw(container, states);
            target.draw(text, states);
        }
    }
}