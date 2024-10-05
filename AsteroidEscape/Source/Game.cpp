#include "Game.h"
#include <iostream>

namespace asteroidescape
{

    Game::Game()
        : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroid Escape")
        , _asteroidPool(_assets, 100)
        , _bulletPool(_assets, 30)
        , _player(_assets, _bulletPool)
        , _spawnCooldown(2.0f)
        , _score(0)
        , _level(1)
        , _scoreToNextLevel(100)
        , _isGameStarted(false)
        , _isGameOver(false)
        , _soundManager(NULL)
    {

        _health = _player.GetCurrentHealth();
        _window.setFramerateLimit(60);

        if (!_font.loadFromFile("../Assets/Fonts/SyneMono-Regular.ttf"))
        {
            throw std::runtime_error("Failed to load font");
        }

        _soundManager = SoundManager::GetInstance();

        InitialiseHUD();

        InitialiseStartScreen();

        InitialiseGameOverScreen();
    }

    Game::~Game()
    {
        delete _soundManager;
    }

    void Game::run()
    {
        while (_window.isOpen())
        {
            ProcessEvents();

            if (_isGameOver)
            {
                // Render game over screen
                DrawGameOver();
            }
            else if (_isGameStarted)
            {
                OnUpdate(); // Only update the game if it has started
                OnRender(); // Only render if it has started
            }
            else
            {
                DrawStartScreen(); // Draw the start screen if the game hasn't started
            }
        }
    }

    void Game::ProcessEvents()
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (!_isGameStarted && !_isGameOver)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                        if (_startText.getGlobalBounds().contains(mousePos))
                        {
                            StartGame();
                        }

                        if (_quitText.getGlobalBounds().contains(mousePos))
                        {
                            _window.close();
                        }
                    }
                }
            }

            if (_isGameOver)
            {
                // Handle keyboard input for restarting or quitting the game
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::R)
                    {
                        RestartGame();
                    }
                    else if (event.key.code == sf::Keyboard::Q)
                    {
                        _window.close();
                    }
                }
            }
        }

        if (!_isGameOver)
        {
            _player.HandleInputs(); // Only handle player input if the game is not over
        }
    }

    void Game::OnUpdate()
    {
        if (_isGameOver)
        {
            return; // Skip updates if the game is over
        }

        float deltaTime = _clock.restart().asSeconds();
        _player.Update(deltaTime);

        // To Spawn asteroids
        _spawnCooldown -= deltaTime;
        if (_spawnCooldown <= 0.0f)
        {
            SpawnAsteroid(sf::Vector2f(rand() % 800, -50));
            _spawnCooldown = std::max(0.5f, 2.0f / _level);
        }

        for (auto& asteroid : _asteroidPool.GetObjects())
        {
            if (asteroid->IsActive())
            {
                asteroid->Update(deltaTime);

                // Check if the asteroid is off-screen
                if (asteroid->getSprite().getPosition().y > _window.getSize().y)
                {
                    _asteroidPool.Release(asteroid.get());
                }
            }
        }

        for (auto& bullet : _bulletPool.GetObjects())
        {
            if (bullet->IsActive())
            {
                bullet->Update(deltaTime);
            }
        }
        _particleSystem.Update(deltaTime);

        // Handle collisions
        HandleCollisions();
    }

    void Game::OnRender()
    {
        _window.clear();

        // Draw all active bullets
        for (auto& bullet : _bulletPool.GetObjects())
        {
            if (bullet->IsActive())
            {
                bullet->Draw(_window);
            }
        }

        _player.Draw(_window);

        // Render all active asteroids
        for (const auto& asteroid : _asteroidPool.GetObjects())
        {
            if (asteroid->IsActive())
            {
                asteroid->Draw(_window);
            }
        }

        _particleSystem.Render(_window);

        _window.draw(_scoreText);
        _window.draw(_levelText);
        _window.draw(_healthText);

        _window.display();
    }

    void Game::SpawnAsteroid(const sf::Vector2f& position)
    {

        Asteroid* asteroid = _asteroidPool.Acquire();
        if (asteroid)
        {
            asteroid->SetPosition(position);
        }
    }

    void Game::HandleCollisions()
    {
        sf::FloatRect playerBounds = _player.getSprite().getGlobalBounds();

        for (auto& asteroid : _asteroidPool.GetObjects())
        {
            if (asteroid->IsActive())
            {
                sf::Sprite asteroidSprite = asteroid->getSprite();
                sf::FloatRect asteroidBounds = asteroidSprite.getGlobalBounds();

                // Check collision with player
                if (playerBounds.intersects(asteroidBounds))
                {
                    _player.UpdateHealth(-asteroid->GetDestructcionPoint());
                    _health = _player.GetCurrentHealth();
                    UpdateHealthText();
                    _particleSystem.CreateParticles(_player.getSprite().getPosition() + sf::Vector2f(playerBounds.width / 2, 0), 20);
                    _asteroidPool.Release(asteroid.get());
                    if (_health <= 0)
                    {
                        _isGameOver = true;
                        _soundManager->StopMusic();
                        _soundManager->PlaySound("gameover");
                        _finalScoreText.setString("Final Score: " + std::to_string(_score));
                        _finalLevelText.setString("Level Reached: " + std::to_string(_level));
                        return;
                    }
                }

                // Check collision with bullets
                for (auto& bullet : _bulletPool.GetObjects())
                {
                    if (bullet->IsActive())
                    {
                        sf::FloatRect bulletBounds = bullet->getSprite().getGlobalBounds();

                        if (bulletBounds.intersects(asteroidBounds))
                        {
                            _particleSystem.CreateParticlesWithSound(asteroidSprite.getPosition() + sf::Vector2f(asteroidBounds.width / 2, asteroidBounds.height / 2), "explosion"); // Create 20 particles at asteroid position
                            UpdateScoreText(asteroid->GetDestructcionPoint());
                            _asteroidPool.Release(asteroid.get());
                            _bulletPool.Release(bullet.get());
                            if (_score >= _scoreToNextLevel)
                            {
                                IncreaseLevel();
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    void Game::RestartGame()
    {
        _isGameOver = false;
        _score = 0;
        _level = 1;
        _health = 100;
        _scoreToNextLevel = 100;
        _spawnCooldown = 2.0f;
        _asteroidPool.Clear();
        _player.Reset();
        UpdateScoreText();
        UpdateLevelText();
        UpdateHealthText();
        _soundManager->PlayMusic();
    }


    void Game::InitialiseHUD()
    {
        // Set up the score text object
        _scoreText.setFont(_font);
        _scoreText.setCharacterSize(24);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setPosition(10.f, 10.f);
        UpdateScoreText();


        // Set up the level text object
        _levelText.setFont(_font);
        _levelText.setCharacterSize(24);
        _levelText.setFillColor(sf::Color::White);
        _levelText.setPosition(10.f, 40.f);  // Position it below the score
        UpdateLevelText();

        // Set up the level text object
        _healthText.setFont(_font);
        _healthText.setCharacterSize(24);
        _healthText.setFillColor(sf::Color::White);
        _healthText.setPosition(10.f, 70.f);  // Position it below the score
        UpdateHealthText();
    }

    void Game::InitialiseStartScreen()
    {
        // Set up the title text
        _titleText.setFont(_font);
        _titleText.setCharacterSize(48);
        _titleText.setFillColor(sf::Color::White);
        _titleText.setString("Space Escape");
        _titleText.setPosition(250.f, 100.f); // Center title on screen

        // Set up the start text
        _startText.setFont(_font);
        _startText.setCharacterSize(36);
        _startText.setFillColor(sf::Color::Green);
        _startText.setString("Start Game");
        _startText.setPosition(300.f, 250.f); // Position for Start button

        // Set up the quit text
        _quitText.setFont(_font);
        _quitText.setCharacterSize(36);
        _quitText.setFillColor(sf::Color::Red);
        _quitText.setString("Quit");
        _quitText.setPosition(350.f, 350.f); // Position for Quit button
    }

    void Game::InitialiseGameOverScreen()
    {
        // Set up the game over text
        _gameOverText.setFont(_font);
        _gameOverText.setCharacterSize(48);
        _gameOverText.setFillColor(sf::Color::Red);
        _gameOverText.setString("Game Over");
        CentraliseText(_gameOverText, -120); // Center the text with an upward offset

        // Set up the restart text
        _restartText.setFont(_font);
        _restartText.setCharacterSize(36);
        _restartText.setFillColor(sf::Color::Green);
        _restartText.setString("Press R to Restart or Q to Quit");
        CentraliseText(_restartText, 30); // Center the text with a downward offset

        // Set up the final score text
        _finalScoreText.setFont(_font);
        _finalScoreText.setCharacterSize(36);
        _finalScoreText.setFillColor(sf::Color::White);
        _finalScoreText.setString("Final Score: 0");
        CentraliseText(_finalScoreText, -60); // Center the text slightly below the game over text

        // Set up the final level text
        _finalLevelText.setFont(_font);
        _finalLevelText.setCharacterSize(36);
        _finalLevelText.setFillColor(sf::Color::White);
        _finalLevelText.setString("Level Reached: 0");
        CentraliseText(_finalLevelText, -20);
    }

    void Game::CentraliseText(sf::Text& text, float offset)
    {
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(_window.getSize().x / 2, _window.getSize().y / 2 + offset);
    }


    void Game::UpdateScoreText(int updateScore)
    {
        _score += updateScore;
        _scoreText.setString("Score: " + std::to_string(_score));
    }

    void Game::UpdateLevelText()
    {
        _levelText.setString("Level: " + std::to_string(_level));
    }

    void Game::UpdateHealthText()
    {
        _healthText.setString("Health: " + std::to_string(static_cast<int>(_health)));
    }

    void Game::IncreaseLevel()
    {
        _level += 1;
        _scoreToNextLevel = _level * 100;
        UpdateLevelText();
    }

    void Game::DrawStartScreen()
    {
        _window.clear();
        _window.draw(_titleText);
        _window.draw(_startText);
        _window.draw(_quitText);
        _window.display();
    }

    void Game::DrawGameOver() {
        _window.clear();
        _window.draw(_gameOverText);
        _window.draw(_finalScoreText);
        _window.draw(_finalLevelText);
        _window.draw(_restartText);
        _window.display();
    }

    void Game::StartGame()
    {
        _isGameStarted = true;
    }

}