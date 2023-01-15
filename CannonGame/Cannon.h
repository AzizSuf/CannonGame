#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Cannon : public sf::Drawable, public sf::Transformable
{
    enum class State
    {
        IDLE,
        Fire,
    };

public:
    Cannon();
    void moveBarrel(double angle);
    void smoothMoveBarrel(double angle);
    void aimBarrelToPoint(sf::Vector2i pointPos);


    void fire();
    void reload();
    void debugDump();
    void update(sf::Time time);

private:
    // FIXME: ѕереместить управление ресурсами в другое место
    void loadAssets();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    

private:
    const double barrelMaxRightAngle = -80;
    const double barreMaxLeftAngle = 30;

    sf::Texture m_lafetTexture;
    sf::Sprite m_lafetSprite;

    sf::Texture m_barrelTexture;
    sf::Sprite m_barrelSprite;

    sf::CircleShape m_ball;

    double m_barrelAngle;

    State m_state = State::IDLE;
    sf::Clock m_clock;
};

