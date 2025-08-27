#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "AssetManager.h"
#include "GenericObjectPool.h"
#include "ParticleSystem.h"
#include "SoundManager.h"
#include "GameState.h"

namespace asteroidescape
{
    class Game
    {
    public:
        Game();
        ~Game();
        void run();
        void quit();
        void ChangeState(std::unique_ptr<GameState> newState);

        // Accessors for states
        sf::RenderWindow& GetWindow() { return _window; }
        Player& GetPlayer() { return _player; }
        GenericObjectPool<Asteroid>& GetAsteroidPool() { return _asteroidPool; }
        GenericObjectPool<Bullet>& GetBulletPool() { return _bulletPool; }
        ParticleSystem& GetParticleSystem() { return _particleSystem; }
        sf::Text& GetScoreText() { return _scoreText; }
        sf::Text& GetLevelText() { return _levelText; }
        sf::Text& GetHealthText() { return _healthText; }

    private:
        sf::RenderWindow _window;
        std::unique_ptr<GameState> _currentState;

        // Game objects
        AssetManager _assets;
        ParticleSystem _particleSystem;
        Player _player;
        GenericObjectPool<Asteroid> _asteroidPool;
        GenericObjectPool<Bullet> _bulletPool;

        // HUD
        sf::Font _font;
        sf::Text _scoreText;
        sf::Text _levelText;
        sf::Text _healthText;

        bool _running = true;
        SoundManager* _soundManager;

        void InitialiseHUD();
    };
}
