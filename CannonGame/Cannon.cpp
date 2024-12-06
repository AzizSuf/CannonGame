#include "Cannon.h"
#include "utils.h"


Cannon::Cannon() :
    m_barrelAngle(0.0)
{
    loadAssets();
    moveBarrel(m_barrelAngle);
}

void Cannon::moveBarrel(double angle)
{
    //std::cout << "angle:::  " << angle << std::endl;
    if (angle < barreMaxLeftAngle || angle > barrelMaxRightAngle)
    {
        return;
    }

    m_barrelSprite.setRotation(angle);
    m_barrelAngle = angle;
}

void Cannon::moveBarrelSmooth(double angle)
{
   // if (m_state == State::IDLE)
   {
        m_barrelTargetAngle = angle;
        //std::cout << "barrelTarget: " << m_barrelTargetAngle << std::endl;
        m_state = State::MovingBarrel;

    }
}

void Cannon::aimBarrelToPoint(sf::Vector2i pointPos)
{
#if 1
    sf::Vector2f barrelGlobalOrigin = m_barrelSprite.getPosition()/* + m_barrelSprite.getOrigin()*/;
    //std::cout << barrelGlobalOrigin.x << std::endl;

    // Calculate barrel angle
    double newBarrelAngle = radiandsToDegrees(atan(((barrelGlobalOrigin.y - pointPos.y) / (pointPos.x - barrelGlobalOrigin.x))));
    //double newBarrelAngle = 
    //std::cout << "New Barrel Angle: " << -newBarrelAngle << std::endl;
    //std::cout << "Barrel Global Origin: " << barrelGlobalOrigin.x << "  " << barrelGlobalOrigin.y << std::endl;
    //debugDump();

    double distance = sqrt((barrelGlobalOrigin.y - m_ball.getPosition().y) + (m_ball.getPosition().x - barrelGlobalOrigin.x));

    sf::Vector2f pos(cos(-newBarrelAngle) * 200, sin(-newBarrelAngle) * 200);

   // const double barrelOriginToEndDistance = 200;

    //m_ball.setPosition(barrelGlobalOrigin.x + cos(degreesToRadians(-newBarrelAngle)) * barrelOriginToEndDistance, barrelGlobalOrigin.y + sin(degreesToRadians(-newBarrelAngle)) * barrelOriginToEndDistance);
    moveBarrelSmooth(-newBarrelAngle);

#endif
}

void Cannon::fire(Projectile& pr)
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

    sf::Vector2f barrelGlobalOrigin = m_barrelSprite.getPosition()/* + m_barrelSprite.getOrigin()*/;
    const float barrelOriginToEndDistance = 200;
    pr.setInitialPosition(sf::Vector2f(barrelGlobalOrigin.x + cos(degreesToRadians(m_barrelAngle)) * barrelOriginToEndDistance, barrelGlobalOrigin.y + sin(degreesToRadians(m_barrelAngle)) * barrelOriginToEndDistance));
    pr.launch(m_barrelAngle);

    m_shotSound.play();
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
    switch (m_state)
    {
    case Cannon::State::IDLE:
        break;
    case Cannon::State::Fire:
        if (m_clock.getElapsedTime().asMilliseconds() > 1)
        {
            // Move ball
            // double angleRad = degreesToRadians(m_barrelAngle);
            // m_ball.move(cos(angleRad) * 5, sin(angleRad) * 5);
            //m_clock.restart();
        }
        break;
    case Cannon::State::MovingBarrel:
        if (m_clock.getElapsedTime().asMicroseconds() > 200)
        {
            if (abs(abs(m_barrelTargetAngle) - abs(m_barrelAngle)) > 1)
            {
                //std::cout << "TESTTT" << std::endl;
                //m_barrelSprite.rotate(1);
                // m_barrelAngle = m_barrelSprite.getRotation();
                if (m_barrelTargetAngle <  m_barrelAngle)
                {
                    moveBarrel(m_barrelAngle - 0.5);

                }
                else // >=
                {
                    moveBarrel(m_barrelAngle + 0.5);
                }
            }
            else
            {
                m_state = State::IDLE;
                //std::cout << "IDLE was setted!" << std::endl;
            }
            m_clock.restart();
        }
        break;
    default:
        break;
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

    if (!m_shotSoundBuffer.loadFromFile("Resources/shot.wav"))
    {

    }

    m_shotSound.setBuffer(m_shotSoundBuffer);
    m_shotSound.setVolume(2);


    const int ballRadius = 13;
    m_ball.setRadius(ballRadius);
    m_ball.setOrigin(ballRadius, ballRadius);
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
    //target.draw(m_ball, states);
    target.draw(m_barrelSprite, states);
    target.draw(m_lafetSprite, states);
}
