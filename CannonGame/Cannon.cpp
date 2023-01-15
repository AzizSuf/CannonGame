#include "Cannon.h"

double degreesToRadians(double degrees)
{
    return degrees * 3.1415 / 180.0;
}

double radiandsToDegrees(double radians)
{
    return radians * 180.0 / 3.1415;
 }


Cannon::Cannon() :
    m_barrelAngle(0.0)
{
    loadAssets();
    moveBarrel(m_barrelAngle);
}

void Cannon::moveBarrel(double angle)
{
    m_barrelSprite.rotate(angle);
    m_barrelAngle += angle;
}

void Cannon::aimBarrelToPoint(sf::Vector2i pointPos)
{
    


  
#if 1
    sf::Vector2f barrelGlobalOrigin = m_barrelSprite.getPosition() + m_barrelSprite.getOrigin();
   
    std::cout << barrelGlobalOrigin.x << std::endl;

    


    // Calculate barrel angle
    double newBarrelAngle = 180.0 / 3.1415 * atan(((barrelGlobalOrigin.y - pointPos.y) / (pointPos.x - barrelGlobalOrigin.x)));
    //double newBarrelAngle = 
    std::cout << "new angle: " << newBarrelAngle << std::endl;


    //if (newBarrelAngle < barreMaxLeftAngle && newBarrelAngle > barrelMaxRightAngle)
   // {
        // Calculate distance
        double distance = sqrt((barrelGlobalOrigin.y - m_ball.getPosition().y) + (m_ball.getPosition().x - barrelGlobalOrigin.x));

        sf::Vector2f pos(cos(-newBarrelAngle) * 200, sin(-newBarrelAngle) * 200);

        m_ball.setPosition(barrelGlobalOrigin.x + cos(degreesToRadians(-newBarrelAngle)) * 100, barrelGlobalOrigin.y + sin(degreesToRadians(-newBarrelAngle)) * 100);

        // Move barrel to initial position
        m_barrelSprite.rotate(-m_barrelAngle);
        m_barrelAngle = 0;

        m_barrelSprite.rotate(-newBarrelAngle);
        m_barrelAngle = -newBarrelAngle;
  //  }

#endif
}

void Cannon::fire()
{
    if (m_state == State::IDLE)
    {
        m_state = State::Fire;
    }
    else if (m_state == State::Fire)
    {
        m_state = State::IDLE;
        m_ball.setPosition(100, 100);
    }
}

void Cannon::reload()
{
}

void Cannon::debugDump()
{
    std::cout << "Barrel Angle: " << m_barrelAngle << "\n";
    std::cout << "BarrelSprite Position x: " << m_barrelSprite.getPosition().x << " y: "<< m_barrelSprite.getPosition().y << "\n";
    std::cout << "BarrelSprite GBounds x: " <<  m_barrelSprite.getGlobalBounds().left << " y: " << m_barrelSprite.getGlobalBounds().top<< "\n";
    std::cout << "State" << static_cast<int>(m_state) << "\n";


    std::cout << std::endl;
}

void Cannon::update(sf::Time time)
{
    if (m_state == State::Fire)
    {
        if (m_clock.getElapsedTime().asMilliseconds() > 1)
        {
            // Move ball
            double angleRad = m_barrelAngle * 3.1415 / 180.0;
            m_ball.move(cos(angleRad) * 1, sin(angleRad) * 1);
            m_clock.restart();
        }
    }
}

void Cannon::loadAssets()
{
    if (!m_lafetTexture.loadFromFile("Resources/CannonLafet.png"))
    {
        // Here is a error
    }

    if (!m_barrelTexture.loadFromFile("Resources/CannonBarrel_ilustr.png"))
    {

    }

    m_barrelTexture.setSmooth(true);

    std::cout << m_lafetTexture.getSize().x << "   " << m_lafetTexture.getSize().y << std::endl;

    m_lafetSprite.setTexture(m_lafetTexture);
    m_barrelSprite.setTexture(m_barrelTexture);

    m_lafetSprite.move(0, 580);
    m_barrelSprite.move(0, 580);

    m_barrelSprite.setOrigin(m_lafetTexture.getSize().x / 2.0, m_barrelTexture.getSize().y/2);
    m_barrelSprite.move(m_lafetTexture.getSize().x - 50, 30);


    m_ball.setRadius(20);
    m_ball.setFillColor(sf::Color::Cyan);
    m_ball.setPosition(390, 588);

}

void Cannon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    //states.texture = &m_tileset;

    // draw the objects
    target.draw(m_barrelSprite, states);
    target.draw(m_lafetSprite, states);
    target.draw(m_ball, states);
}
