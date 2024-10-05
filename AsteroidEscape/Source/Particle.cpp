#include "Particle.h"

/*
-----------------------------------------------------------------------------------------------------------
// Can be used as a GameObject, but here I want to treat it as a shape object instead of a textured object.
-----------------------------------------------------------------------------------------------------------
*/
namespace asteroidescape
{

    Particle::Particle(const sf::Vector2f& position)
    {
        // Initialize 
        _shape.setRadius(2.0f); // particle size
        _shape.setPosition(position);

        // Random color codes for golden shadee
        int red = 255;
        int green = 200 + rand() % 56;
        int blue = rand() % 256;

        _shape.setFillColor(sf::Color(red, green, blue));

        // Random angle in radians (0 to 2 * PI)
        float angle = static_cast<float>(rand() % 360) * (3.14159f / 180.0f); // Convert degrees to radians

        float speed = (rand() % 1000) / 10.f; // Random speed between 0 and 10

        // Calculate the velocity based on the angle
        _velocity.x = speed * cos(angle);
        _velocity.y = speed * sin(angle);

        // Set a random lifetime between 0.5 and 1.5 seconds
        _lifetime = (rand() % 100) / 50.0f + 0.5f;
    }

    void Particle::Update(float deltaTime)
    {
        // Move the particle based on its velocity
        _shape.move(_velocity * deltaTime);

        // Decrease lifetime
        _lifetime -= deltaTime;
    }

    bool Particle::IsAlive() const
    {
        return _lifetime > 0;
    }

    void Particle::Draw(sf::RenderWindow& window) {
        window.draw(_shape);
    }

}