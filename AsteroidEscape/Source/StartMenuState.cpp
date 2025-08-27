#include "StartMenuState.h"
#include "Game.h"
#include "PlayingState.h"
#include <iostream>

namespace asteroidescape
{
    StartMenuState::StartMenuState()
    {
        if (!_font.loadFromFile("../Assets/Fonts/SyneMono-Regular.ttf"))
        {
            throw std::runtime_error("Failed to load font");
        }

        _titleText.setFont(_font);
        _titleText.setString("Space Escape");
        _titleText.setCharacterSize(48);
        _titleText.setFillColor(sf::Color::White);

        _startText.setFont(_font);
        _startText.setString("Start Game");
        _startText.setCharacterSize(36);
        _startText.setFillColor(sf::Color::Green);

        _quitText.setFont(_font);
        _quitText.setString("Quit");
        _quitText.setCharacterSize(36);
        _quitText.setFillColor(sf::Color::Red);
    }

    void StartMenuState::CentraliseText(sf::Text& text, sf::RenderWindow& window, float offset)
    {
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
        text.setPosition(window.getSize().x / 2, window.getSize().y / 2 + offset);
    }

    void StartMenuState::HandleInput(Game& game, sf::Event& event)
    {
        if (event.type == sf::Event::Closed)
            game.quit();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (_startText.getGlobalBounds().contains(mousePos))
            {
                game.ChangeState(std::make_unique<PlayingState>());
            }
            else if (_quitText.getGlobalBounds().contains(mousePos))
            {
                game.quit();
            }
        }
    }

    void StartMenuState::Update(Game& game, float dt)
    {
        // nothing to update for menu
    }

    void StartMenuState::Render(Game& game)
    {
        sf::RenderWindow& window = game.GetWindow();
        window.clear();

        CentraliseText(_titleText, window, -150.f);
        CentraliseText(_startText, window, 0.f);
        CentraliseText(_quitText, window, 100.f);

        window.draw(_titleText);
        window.draw(_startText);
        window.draw(_quitText);

        window.display();
    }
}
