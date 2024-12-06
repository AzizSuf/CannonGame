#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Projectile.h"

class Cannon : public sf::Drawable, public sf::Transformable
{
    enum class State
    {
        IDLE,
        Fire,
        MovingBarrel
    };
public:
    Cannon();
    void moveBarrel(double angle);
    void moveBarrelSmooth(double angle);
    void aimBarrelToPoint(sf::Vector2i pointPos);
    void fire(Projectile& pr);
    void reload();
    void update(sf::Time time);
    void debugDump();

private:
    void loadAssets();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    const double barreMaxLeftAngle = -80;
    const double barrelMaxRightAngle = 20;
    sf::Texture m_lafetTexture;
    sf::Sprite m_lafetSprite;
    sf::Texture m_barrelTexture;
    sf::Sprite m_barrelSprite;
    sf::CircleShape m_ball;
    double m_barrelAngle;
    double m_barrelTargetAngle;
    sf::SoundBuffer m_shotSoundBuffer;
    sf::Sound m_shotSound;
    sf::Shader m_fireShader;
    State m_state = State::IDLE;
    sf::Clock m_clock;
};

