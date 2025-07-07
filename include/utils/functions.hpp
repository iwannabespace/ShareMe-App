#ifndef COMMON_HPP
#define COMMON_HPP

#include "../pages/page.hpp"
#include "../api/authorization_data.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

namespace ShareMe
{
    namespace Functions
    {
        void FitText(sf::Text& text, sf::Vector2f size);
        float GetMiddle(float object, float container, float start, float minus);
        float GetTextMaxHeight(const sf::Text& text);
        std::string GenerateSalt(size_t length);
        std::string SHA256(const std::string& data);
        bool SaveTokens(const AuthorizationData& authorizationData);
        std::optional<AuthorizationData> GetTokens();
    }
}

#endif