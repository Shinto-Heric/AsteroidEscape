#include "PlayingState.h"
#include "Game.h"
#include "GameOverState.h"
#include <algorithm>
#include <iostream>

namespace asteroidescape
{
    PlayingState::PlayingState()
        : _spawnCooldown(2.0f), _score(0), _level(1), _scoreToNextLevel(100)
    {
    }

    void PlayingState::HandleInput(Game& game, sf::Event& event)
    {
        if (event.type == sf::Event::Closed)
            game.quit();

        game.GetPlayer().HandleInputs();
    }

    void PlayingState::Update(Game& game, float dt)
    {
        float deltaTime = _clock.restart().asSeconds();

        game.GetPlayer().Update(deltaTime);

        // Spawn asteroids
        _spawnCooldown -= deltaTime;
        if (_spawnCooldown <= 0.f)
        {
            SpawnAsteroid(game);
            _spawnCooldown = std::max(0.5f, 2.0f / _level);
        }

        // Update asteroids
        for (auto& asteroid : game.GetAsteroidPool().GetObjects())
        {
            if (asteroid->IsActive())
            {
                asteroid->Update(deltaTime);

                // Off-screen release
                if (asteroid->getSprite().getPosition().y > game.GetWindow().getSize().y)
                    game.GetAsteroidPool().Release(asteroid.get());
            }
        }

        // Update bullets
        for (auto& bullet : game.GetBulletPool().GetObjects())
        {
            if (bullet->IsActive())
                bullet->Update(deltaTime);
        }

        game.GetParticleSystem().Update(deltaTime);

        // Handle collisions and scoring
        HandleCollisions(game);

        // Update HUD
        game.GetScoreText().setString("Score: " + std::to_string(_score));
        game.GetLevelText().setString("Level: " + std::to_string(_level));
        game.GetHealthText().setString("Health: " + std::to_string(static_cast<int>(game.GetPlayer().GetCurrentHealth())));
    }

    void PlayingState::Render(Game& game)
    {
        sf::RenderWindow& window = game.GetWindow();
        window.clear();

        // Draw bullets
        for (auto& bullet : game.GetBulletPool().GetObjects())
            if (bullet->IsActive())
                bullet->Draw(window);

        // Draw player
        game.GetPlayer().Draw(window);

        // Draw asteroids
        for (auto& asteroid : game.GetAsteroidPool().GetObjects())
            if (asteroid->IsActive())
                asteroid->Draw(window);

        // Draw particles
        game.GetParticleSystem().Render(window);

        // Draw HUD
        window.draw(game.GetScoreText());
        window.draw(game.GetLevelText());
        window.draw(game.GetHealthText());

        window.display();
    }

    void PlayingState::HandleCollisions(Game& game)
    {
        sf::FloatRect playerBounds = game.GetPlayer().getSprite().getGlobalBounds();

        for (auto& asteroid : game.GetAsteroidPool().GetObjects())
        {
            if (!asteroid->IsActive()) continue;

            sf::FloatRect asteroidBounds = asteroid->getSprite().getGlobalBounds();

            // Player collision
            if (playerBounds.intersects(asteroidBounds))
            {
                game.GetPlayer().UpdateHealth(-asteroid->GetDestructcionPoint());
                game.GetParticleSystem().CreateParticles(game.GetPlayer().getSprite().getPosition() + sf::Vector2f(playerBounds.width / 2, 0), 20);
                game.GetAsteroidPool().Release(asteroid.get());

                if (game.GetPlayer().GetCurrentHealth() <= 0)
                {
                    // Game over
                    game.ChangeState(std::make_unique<GameOverState>(_score, _level));
                    return;
                }
            }

            // Bullet collision
            for (auto& bullet : game.GetBulletPool().GetObjects())
            {
                if (!bullet->IsActive()) continue;

                sf::FloatRect bulletBounds = bullet->getSprite().getGlobalBounds();

                if (bulletBounds.intersects(asteroidBounds))
                {
                    game.GetParticleSystem().CreateParticlesWithSound(
                        asteroid->getSprite().getPosition() + sf::Vector2f(asteroidBounds.width / 2, asteroidBounds.height / 2),
                        "explosion"
                    );

                    _score += asteroid->GetDestructcionPoint();
                    game.GetAsteroidPool().Release(asteroid.get());
                    game.GetBulletPool().Release(bullet.get());

                    if (_score >= _scoreToNextLevel)
                    {
                        _level++;
                        _scoreToNextLevel = _level * 100;
                    }

                    break; // exit bullet loop
                }
            }
        }
    }

    void PlayingState::SpawnAsteroid(Game& game)
    {
        Asteroid* asteroid = game.GetAsteroidPool().Acquire();
        if (asteroid)
        {
            asteroid->SetPosition(sf::Vector2f(rand() % 800, -50));
        }
    }

    void PlayingState::Reset(Game& game)
    {
        _score = 0;
        _level = 1;
        _scoreToNextLevel = 100;
        _spawnCooldown = 2.0f;

        game.GetAsteroidPool().Clear();
        game.GetBulletPool().Clear();
        game.GetPlayer().Reset();
    }
}
