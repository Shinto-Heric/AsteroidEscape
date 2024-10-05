#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#define ASTRO_COUNT 3

namespace asteroidescape
{
    class AssetManager
    {
    public:
        AssetManager();
        sf::Texture& GetTexture(const std::string& filename);

    private:
        std::map<std::string, sf::Texture> _textures;
        void LoadTexture(const std::string& filename);
    };
}

