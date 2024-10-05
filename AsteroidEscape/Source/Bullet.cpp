#include "Bullet.h"

namespace asteroidescape
{

    Bullet::Bullet(AssetManager& assets)
        : _speed(-500.f)
    {
        _sprite.setTexture(assets.GetTexture("bullet"));

    }

    void Bullet::Update(float deltaTime)
    {
        if (_active)
        {
            // Move the bullet upwards (negative y-direction)
            _sprite.move(0, _speed * deltaTime);

            // If the bullet moves off-screen, deactivate it
            if (_sprite.getPosition().y < 0)
            {
                _active = false;
            }
        }
    }

    void Bullet::Draw(sf::RenderWindow& window)
    {
        if (_active)
        {
            window.draw(_sprite);
        }
    }
}