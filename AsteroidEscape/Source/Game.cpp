#include "Game.h"
#include "StartMenuState.h"
#include <iostream>

namespace asteroidescape
{
    Game::Game()
        : _window(sf::VideoMode(800, 600), "Asteroid Escape")
        , _asteroidPool(_assets, 100)
        , _bulletPool(_assets, 30)
        , _player(_assets, _bulletPool)
    {
        _window.setFramerateLimit(60);
        _soundManager = SoundManager::GetInstance();

        if (!_font.loadFromFile("../Assets/Fonts/SyneMono-Regular.ttf"))
            throw std::runtime_error("Failed to load font");

        InitialiseHUD();
        _currentState = std::make_unique<StartMenuState>();
    }

    Game::~Game()
    {
        delete _soundManager;
    }

    void Game::run()
    {
        sf::Clock clock;
        while (_window.isOpen() && _running)
        {
            sf::Event event;
            while (_window.pollEvent(event))
            {
                if (_currentState)
                    _currentState->HandleInput(*this, event);
            }

            float dt = clock.restart().asSeconds();
            if (_currentState)
                _currentState->Update(*this, dt);

            if (_currentState)
                _currentState->Render(*this);
        }
    }

    void Game::quit()
    {
        _running = false;
        _window.close();
    }

    void Game::ChangeState(std::unique_ptr<GameState> newState)
    {
        _currentState = std::move(newState);
    }

    void Game::InitialiseHUD()
    {
        _scoreText.setFont(_font);
        _scoreText.setCharacterSize(24);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setPosition(10.f, 10.f);

        _levelText.setFont(_font);
        _levelText.setCharacterSize(24);
        _levelText.setFillColor(sf::Color::White);
        _levelText.setPosition(10.f, 40.f);

        _healthText.setFont(_font);
        _healthText.setCharacterSize(24);
        _healthText.setFillColor(sf::Color::White);
        _healthText.setPosition(10.f, 70.f);
    }
}
