#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

namespace asteroidescape
{
    class PlayingState : public GameState
    {
    public:
        PlayingState();

        void HandleInput(Game& game, sf::Event& event) override;
        void Update(Game& game, float dt) override;
        void Render(Game& game) override;
        void Reset(Game& game);


    private:
        void HandleCollisions(Game& game);
        void SpawnAsteroid(Game& game);

        sf::Clock _clock;
        float _spawnCooldown;
        int _score;
        int _level;
        int _scoreToNextLevel;
    };
}
