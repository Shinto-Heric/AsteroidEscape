#include "Player.h"

namespace asteroidescape
{
    Player::Player(AssetManager& assets, GenericObjectPool<Bullet>& bulletPool)
        : _bulletPool(bulletPool)
        , _shootCooldown(0.5f)
        , _shootTimer(0.f)
        , _speed(300.0f)
        , _currentHealth(HEALTH)
    {
        _sprite.setTexture(assets.GetTexture("spaceship"));

        _sprite.setPosition(INITIAL_POSITION_X, INITIAL_POSITION_Y);
    }

    void Player::HandleInputs()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            _sprite.move(-_speed * 0.016f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            _sprite.move(_speed * 0.016f, 0);
        }

        // Handle shooting input (spacebar)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (_shootTimer >= _shootCooldown)
            {
                FireBullet();
                _shootTimer = 0.f;
            }
        }
    }

    void Player::Update(float deltaTime)
    {

        _shootTimer += deltaTime;
        //To ensure the player stays within the screen bounds
        if (_sprite.getPosition().x < 0)
            _sprite.setPosition(0, _sprite.getPosition().y);
        if (_sprite.getPosition().x + _sprite.getGlobalBounds().width > 800)
            _sprite.setPosition(800 - _sprite.getGlobalBounds().width, _sprite.getPosition().y);
    }

    void Player::UpdateHealth(float hp)
    {
        _currentHealth += hp;
    }

    const float Player::GetCurrentHealth() const
    {
        return (_currentHealth / HEALTH) * 100;
    }

    void Player::Reset()
    {
        _sprite.setPosition(INITIAL_POSITION_X, INITIAL_POSITION_Y);
        _shootCooldown = 0.5f;
        _shootTimer = 0.f;
        _currentHealth = HEALTH;
        _bulletPool.Clear();
    }

    void Player::FireBullet()
    {
        Bullet* bullet = _bulletPool.Acquire();
        if (bullet)
        {
            sf::Vector2f bulletPosition = _sprite.getPosition();
            bulletPosition.x += _sprite.getGlobalBounds().width / 2 - 5; // Adjust bullet position
            bullet->SetPosition(bulletPosition);
            SoundManager::GetInstance()->PlaySound("shoot");
        }
    }
}