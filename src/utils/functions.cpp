#include "../../include/utils/functions.hpp"
#include "../../include/pages/page.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>

namespace ShareMe
{
    namespace Functions
    {
        void FitText(sf::Text& text, sf::Vector2f size)
        {
            for (uint8_t i = 1; true; i++)
            {
                text.setCharacterSize(i);
                
                auto tSize = text.getGlobalBounds().getSize();
                
                if (tSize.x >= size.x || tSize.y >= size.y)
                {
                    text.setCharacterSize(i - 24);
                    break;
                }
            }
        }

        float GetMiddle(float object, float container, float start, float minus)
        {
            return std::round(start + ((container - object) / 2) - minus);
        }

        float GetTextMaxHeight(const sf::Text& text)
        {
            sf::Text temp;
            temp.setFont(*text.getFont());
            temp.setString("qwertyuıopğüasdfghjklşizxcvbnmöçQWERTYUIOPĞÜASDFGHJKLŞİZXCVBNMÖÇ");
            temp.setCharacterSize(text.getCharacterSize());
            
            return temp.getGlobalBounds().height;
        }
    }
}