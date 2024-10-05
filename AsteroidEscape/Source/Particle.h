#pragma once

#include <SFML/Graphics.hpp>

namespace asteroidescape
{
    // Can be used as a GameObject, but here I want to treat it as a shape object instead of a textured object.

    class Particle
    {
    public:
        Particle(const sf::Vector2f& position);

        void Update(float deltaTime);
        bool IsAlive() const;
        void Draw(sf::RenderWindow& window);

    private:
        sf::CircleShape _shape;      // Particle shape (can be changed to sprite if needed)
        sf::Vector2f _velocity;      // Direction and speed of the particle
        float _lifetime;             // How long the particle stays alive
    };
}
