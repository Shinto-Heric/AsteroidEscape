#include "GameOverState.h"
#include "Game.h"
#include "PlayingState.h"
#include <iostream>

namespace asteroidescape
{
    GameOverState::GameOverState(int score, int level)
    {
        if (!_font.loadFromFile("../Assets/Fonts/SyneMono-Regular.ttf"))
        {
            throw std::runtime_error("Failed to load font");
        }

        _gameOverText.setFont(_font);
        _gameOverText.setString("Game Over");
        _gameOverText.setCharacterSize(48);
        _gameOverText.setFillColor(sf::Color::Red);

        _restartText.setFont(_font);
        _restartText.setString("Press R to Restart or Q to Quit");
        _restartText.setCharacterSize(36);
        _restartText.setFillColor(sf::Color::Green);

        _finalScoreText.setFont(_font);
        _finalScoreText.setString("Final Score: " + std::to_string(score));
        _finalScoreText.setCharacterSize(36);
        _finalScoreText.setFillColor(sf::Color::White);

        _finalLevelText.setFont(_font);
        _finalLevelText.setString("Level Reached: " + std::to_string(level));
        _finalLevelText.setCharacterSize(36);
        _finalLevelText.setFillColor(sf::Color::White);
    }

    void GameOverState::CentraliseText(sf::Text& text, sf::RenderWindow& window, float offset)
    {
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
        text.setPosition(window.getSize().x / 2, window.getSize().y / 2 + offset);
    }

    void GameOverState::HandleInput(Game& game, sf::Event& event)
    {
        if (event.type == sf::Event::Closed)
            game.quit();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::R)
            {
                auto newPlayingState = std::make_unique<PlayingState>();
                newPlayingState->Reset(game);  // Reset all gameplay elements
                game.ChangeState(std::move(newPlayingState));
            }
            else if (event.key.code == sf::Keyboard::Q)
            {
                game.quit();
            }
        }
    }

    void GameOverState::Update(Game& game, float dt)
    {
        // nothing to update
    }

    void GameOverState::Render(Game& game)
    {
        sf::RenderWindow& window = game.GetWindow();
        window.clear();

        CentraliseText(_gameOverText, window, -120);
        CentraliseText(_finalScoreText, window, -60);
        CentraliseText(_finalLevelText, window, -20);
        CentraliseText(_restartText, window, 30);

        window.draw(_gameOverText);
        window.draw(_finalScoreText);
        window.draw(_finalLevelText);
        window.draw(_restartText);

        window.display();
    }
}
