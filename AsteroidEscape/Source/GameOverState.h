#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

namespace asteroidescape
{
    class GameOverState : public GameState
    {
    public:
        GameOverState(int score, int level);

        void HandleInput(Game& game, sf::Event& event) override;
        void Update(Game& game, float dt) override;
        void Render(Game& game) override;

    private:
        sf::Font _font;
        sf::Text _gameOverText;
        sf::Text _restartText;
        sf::Text _finalScoreText;
        sf::Text _finalLevelText;

        void CentraliseText(sf::Text& text, sf::RenderWindow& window, float offset = 0.0f);
    };
}
