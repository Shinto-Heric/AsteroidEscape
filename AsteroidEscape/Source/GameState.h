#pragma once
#include <SFML/Graphics.hpp>

namespace asteroidescape
{
    class Game;

    class GameState
    {
    public:
        virtual ~GameState() = default;
        virtual void HandleInput(Game& game, sf::Event& event) = 0;
        virtual void Update(Game& game, float dt) = 0;
        virtual void Render(Game& game) = 0;
    };
}
