#ifndef THEME_HPP
#define THEME_HPP

#include <SFML/Graphics.hpp>

namespace ShareMe
{
    class Theme
    {
    public:
        static const sf::Color Primary;
        static const sf::Color SurfaceTint;
        static const sf::Color OnPrimary;
        static const sf::Color PrimaryContainer;
        static const sf::Color OnPrimaryContainer;
        static const sf::Color Secondary;
        static const sf::Color OnSecondary;
        static const sf::Color SecondaryContainer;
        static const sf::Color OnSecondaryContainer;
        static const sf::Color Tertiary;
        static const sf::Color OnTertiary;
        static const sf::Color TertiaryContainer;
        static const sf::Color OnTertiaryContainer;
        static const sf::Color Error;
        static const sf::Color OnError;
        static const sf::Color ErrorContainer;
        static const sf::Color OnErrorContainer;
        static const sf::Color Background;
        static const sf::Color OnBackground;
        static const sf::Color Surface;
        static const sf::Color OnSurface;
        static const sf::Color SurfaceVariant;
        static const sf::Color OnSurfaceVariant;
        static const sf::Color Outline;
        static const sf::Color OutlineVariant;
        static const sf::Color Shadow;
        static const sf::Color Scrim;
        static const sf::Color InverseSurface;
        static const sf::Color InverseOnSurface;
        static const sf::Color InversePrimary;
        static const sf::Color PrimaryFixed;
        static const sf::Color OnPrimaryFixed;
        static const sf::Color PrimaryFixedDim;
        static const sf::Color OnPrimaryFixedVariant;
        static const sf::Color SecondaryFixed;
        static const sf::Color OnSecondaryFixed;
        static const sf::Color SecondaryFixedDim;
        static const sf::Color OnSecondaryFixedVariant;
        static const sf::Color TertiaryFixed;
        static const sf::Color OnTertiaryFixed;
        static const sf::Color TertiaryFixedDim;
        static const sf::Color OnTertiaryFixedVariant;
        static const sf::Color SurfaceDim;
        static const sf::Color SurfaceBright;
        static const sf::Color SurfaceContainerLowest;
        static const sf::Color SurfaceContainerLow;
        static const sf::Color SurfaceContainer;
        static const sf::Color SurfaceContainerHigh;
        static const sf::Color SurfaceContainerHighest;
        static const sf::Color Disabled;
    };
}

#endif