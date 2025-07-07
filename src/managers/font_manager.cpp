#include "../../include/managers/font_manager.hpp"

namespace ShareMe
{
    FontManager::FontManager()
    {
    }

    FontManager::~FontManager()
    {
    }

    bool FontManager::load(const std::string& path, const std::string& name)
    {
        return fonts[name].openFromFile(path);
    }

    std::optional<sf::Font*> FontManager::get(const std::string& name)
    {
        if (fonts.count(name))
            return &fonts[name];
        
        return std::nullopt;
    }
}