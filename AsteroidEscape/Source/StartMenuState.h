#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

namespace asteroidescape
{
    class StartMenuState : public GameState
    {
    public:
        StartMenuState();

        void HandleInput(Game& game, sf::Event& event) override;
        void Update(Game& game, float dt) override;
        void Render(Game& game) override;

    private:
        sf::Font _font;
        sf::Text _titleText;
        sf::Text _startText;
        sf::Text _quitText;

        void CentraliseText(sf::Text& text, sf::RenderWindow& window, float offset = 0.0f);
    };
}
