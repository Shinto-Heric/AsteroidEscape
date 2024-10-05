#pragma once

#include <SFML/Graphics.hpp>

namespace asteroidescape
{
    class GameObject
    {
    public:
        GameObject();

        // Pure virtual functions
        virtual void Update(float deltaTime) = 0;

        // virtual functions
        virtual void Draw(sf::RenderWindow& window);

        // general functions
        void SetPosition(const sf::Vector2f& position);
        bool IsActive() const;
        void SetActive(bool status);
        sf::Sprite getSprite() const;


    protected:
        sf::Sprite _sprite;
        bool _active;
    };

}