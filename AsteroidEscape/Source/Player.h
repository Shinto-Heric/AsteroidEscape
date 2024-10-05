#pragma once

#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "GenericObjectPool.h"
#include "Bullet.h"
#include "SoundManager.h"

constexpr auto INITIAL_POSITION_X = 400.0f;
constexpr auto INITIAL_POSITION_Y = 500.0f;
constexpr auto HEALTH = 500;

namespace asteroidescape
{
    class Player : public GameObject
    {
    public:
        Player(AssetManager& assets, GenericObjectPool<Bullet>& bulletPool);

        void Update(float deltaTime) override;

        void HandleInputs();
        void UpdateHealth(float hp);
        const float GetCurrentHealth() const;
        void Reset();

    private:
        float _speed;
        float _currentHealth;
        GenericObjectPool<Bullet>& _bulletPool;
        float _shootCooldown;
        float _shootTimer;

        void FireBullet();
    };
}

