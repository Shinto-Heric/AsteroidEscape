#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "AssetManager.h"

namespace asteroidescape
{
    class Asteroid : public GameObject
    {
    public:
        Asteroid(AssetManager& assets);

        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

        int GetDestructcionPoint() const;

    private:
        float _speed;
        int _destructionPoint;
    };
}

