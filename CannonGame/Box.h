#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

class Box : public sf::Drawable, public sf::Transformable
{
public:
    Box();
    sf::FloatRect getGlobalBounds();

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    void move(sf::Vector2f delta);
    void destroy();

    bool isAlive();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite m_boxSprite;
    bool m_isAlive = true;


};

