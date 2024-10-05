#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Asteroid.h"
#include "AssetManager.h"
#include "GenericObjectPool.h"
#include "ParticleSystem.h"
#include "SoundManager.h"

constexpr auto WINDOW_WIDTH = 800.0f;
constexpr auto WINDOW_HEIGHT = 600.0f;
#define FULLSCREEN = 0; // to switch video mode
namespace asteroidescape
{

    class Game
    {
    public:
        Game();
        ~Game();
        void run();

    private:

        void InitialiseHUD();
        void InitialiseStartScreen();
        void InitialiseGameOverScreen();
        void ProcessEvents();
        void OnUpdate();
        void OnRender();

        void HandleCollisions();

        void UpdateScoreText(int score = 0);

        void UpdateLevelText();
        void IncreaseLevel();

        void UpdateHealthText();

        void DrawStartScreen();
        void StartGame();

        void RestartGame();
        void DrawGameOver();

        void CentraliseText(sf::Text& text, float offset = 0.0f);
        void SpawnAsteroid(const sf::Vector2f& position);

        // variables
        int _score;
        int _level;
        int _scoreToNextLevel;
        float _health;
        float _spawnCooldown;

        sf::Clock _clock;

        // font variable
        sf::Font _font;

        // HUD Variables
        sf::Text _scoreText;
        sf::Text _healthText;
        sf::Text _levelText;

        // Start screen variables
        bool _isGameStarted;
        sf::Text _titleText;
        sf::Text _startText;
        sf::Text _quitText;

        // Gameover screen variables
        bool _isGameOver;
        sf::Text _gameOverText;
        sf::Text _restartText;
        sf::Text _finalScoreText;
        sf::Text _finalLevelText;

        //Renderwindow
        sf::RenderWindow _window;

        // AssetManager
        AssetManager _assets;

        // Particle
        ParticleSystem _particleSystem;

        //Player
        Player _player;

        //Objectpool variables
        GenericObjectPool<Asteroid> _asteroidPool;
        GenericObjectPool<Bullet> _bulletPool;

        //Sound
        SoundManager* _soundManager;


    };


}