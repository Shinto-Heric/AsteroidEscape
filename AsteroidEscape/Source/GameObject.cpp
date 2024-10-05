#include "GameObject.h"

namespace asteroidescape
{

    GameObject::GameObject()
        : _active(true)
    {

    }

    void GameObject::Draw(sf::RenderWindow& window)
    {
        if (_active)
        {
            window.draw(_sprite);
        }
    }

    void GameObject::SetPosition(const sf::Vector2f& position)
    {
        _sprite.setPosition(position);
    }

    bool GameObject::IsActive() const
    {
        return _active;
    }

    void GameObject::SetActive(bool status)
    {
        _active = status;
    }

    sf::Sprite GameObject::getSprite() const
    {
        return _sprite;
    }
}