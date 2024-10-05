#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.h"
#include "SoundManager.h"

namespace asteroidescape
{
    class ParticleSystem
    {
    public:
        void CreateParticles(const sf::Vector2f& position, int count = 50);
        void CreateParticlesWithSound(const sf::Vector2f& position, const std::string& filename, int count = 50);

        void Update(float deltaTime);
        void Render(sf::RenderWindow& window);

    private:
        std::vector<Particle> _particles; // Store the active particles
    };
}

