#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "AssetManager.h"

namespace asteroidescape
{
    class Bullet : public GameObject
    {
    public:
        Bullet(AssetManager& assets);

        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        float _speed;
    };
}


