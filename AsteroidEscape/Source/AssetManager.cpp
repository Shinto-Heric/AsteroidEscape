#include "AssetManager.h"

namespace asteroidescape
{
    AssetManager::AssetManager()
    {
        LoadTexture("spaceship");
        for (int i = 1; i <= ASTRO_COUNT; i++)
        {
            LoadTexture("asteroid" + std::to_string(i));
        }
        LoadTexture("bullet");
    }

    void AssetManager::LoadTexture(const std::string& filename)
    {
        sf::Texture texture;
        texture.loadFromFile("../Assets/Textures/" + filename + ".png");
        _textures[filename] = texture;
    }

    sf::Texture& AssetManager::GetTexture(const std::string& filename)
    {
        return _textures.at(filename);
    }

}