#include "ParticleSystem.h"

namespace asteroidescape
{

    void ParticleSystem::CreateParticles(const sf::Vector2f& position, int count)
    {
        // To Create 'count' no of particles at the given position
        for (int i = 0; i < count; ++i) {
            _particles.emplace_back(position);
        }
    }

    void ParticleSystem::CreateParticlesWithSound(const sf::Vector2f& position, const std::string& filename, int count)
    {
        // To reate 'count' no of particles at the given position with sound
        for (int i = 0; i < count; ++i) {
            _particles.emplace_back(position);
        }
        SoundManager::GetInstance()->PlaySound(filename);
    }

    void ParticleSystem::Update(float deltaTime)
    {
        for (auto it = _particles.begin(); it != _particles.end();)
        {
            it->Update(deltaTime);
            if (!it->IsAlive())
            {
                it = _particles.erase(it); // Remove dead particle
            }
            else
            {
                ++it;
            }
        }
    }

    void ParticleSystem::Render(sf::RenderWindow& window)
    {
        for (auto& particle : _particles)
        {
            particle.Draw(window);
        }
    }

}