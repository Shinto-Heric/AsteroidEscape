#include "Asteroid.h"

namespace asteroidescape
{

    Asteroid::Asteroid(AssetManager& assets)
        : _speed(200.0f)
    {
        int randInt = rand() % ASTRO_COUNT + 1;
        _destructionPoint = 0;
        _sprite.setTexture(assets.GetTexture("asteroid" + std::to_string(randInt)));
        _destructionPoint = _destructionPoint + randInt * 10;
    }

    void Asteroid::Update(float deltaTime)
    {
        if (_active)
        {
            _sprite.move(0, _speed * deltaTime);
        }
    }

    void Asteroid::Draw(sf::RenderWindow& window)
    {
        if (_active)
        {
            window.draw(_sprite);
        }
    }

    int Asteroid::GetDestructcionPoint() const
    {
        return _destructionPoint;
    }
}
