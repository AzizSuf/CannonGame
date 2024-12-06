#include "Projectile.h"

Projectile::Projectile()
{
    int ballRadius = 10;
    m_ball.setRadius(ballRadius);
    m_ball.setOrigin(ballRadius, ballRadius);
    m_ball.setFillColor(sf::Color::Cyan);
    m_ball.setPosition(100, 100);

    // Set some default parameters..
    m_physics.setCalcMethod(CalcMethod::Verlet);
    m_physics.setLaunchAngle(45);
    m_physics.setInitialSpeed(20);
    m_physics.setInitialHeight(2);
    m_physics.setSteadySpeed(10);
    m_physics.setWindSpeed(0);
    m_physics.setGravAccel(9.8);
    m_physics.setTimeStep(0.001);

    m_physics.init();
    m_physics.clear();
    
}

void Projectile::launch(double angle)
{
    isFly = true;
    m_flyAngle = angle;
    m_physics.setLaunchAngle(-angle);
    m_physics.init();
    m_physics.clear();
    m_physics.fullUpdate();

#if 0
    for (auto& point : m_physics.getHeightVsDistanceData())
    {
        std::cout << "point: " << "xx" << "   x: " << point.x << " y: " << point.y << "\n";
    }
#endif
    // std::cout << "ph size: " << m_physics.getHeightVsDistanceData().size() << std::endl;
    iter = 0;
}

void Projectile::explode()
{
    m_isAlive = false;
}

bool Projectile::isAlive() const
{
    return m_isAlive;
}

void Projectile::setInitialPosition(sf::Vector2f pos)
{
    m_ball.setPosition(pos);

    //sf::Vector2f(convertPhysicModelToScreenCoords(sf::Vector2f(m_physics.getHeightVsDistanceData()[iter * 10].x, m_physics.getHeightVsDistanceData()[iter * 10].y)));
    
    Vector2d phPos = Vector2d(convertScreenToPhysicModelCoords(pos));
    m_physics.setInitialPosition(phPos);
}

sf::Vector2f Projectile::getPosition() const
{
    return m_ball.getPosition();
}

sf::FloatRect Projectile::getGlobalBounds()
{
    return m_ball.getGlobalBounds();
}

sf::Vector2f Projectile::convertPhysicModelToScreenCoords(sf::Vector2f physicPos)
{
    auto pos = sf::Vector2f(physicPos.x * 100.0f, physicPos.y * 100.0f);
    pos.y = 800 - pos.y;
    return pos;
}

sf::Vector2f Projectile::convertScreenToPhysicModelCoords(sf::Vector2f screenPos)
{
    return sf::Vector2f((sf::Vector2f(screenPos.x, 800- screenPos.y)) / 100.0f);
}

void Projectile::update()
{
    if (isFly)
    {
        if (m_clock.getElapsedTime().asSeconds() > 0.01)
        {
            // Move ball
            double angleRad = degreesToRadians(m_flyAngle);
            //m_ball.move(cos(angleRad) * 10, sin(angleRad) * 10);
            //m_physics.getHeightVsDistanceData()[iter * 10].x * 100 + 100, 800 - m_physics.getHeightVsDistanceData()[iter * 10].y * 100
            sf::Vector2f newPos = sf::Vector2f(convertPhysicModelToScreenCoords(sf::Vector2f(m_physics.getHeightVsDistanceData()[iter * 10].x, m_physics.getHeightVsDistanceData()[iter * 10].y)));
            //std::cout << "x: " << newPos.x << "y: " << newPos.y << "   size: " << m_physics.getHeightVsDistanceData().size()<< std::endl;
            //std::cout << "x: " << m_physics.getHeightVsDistanceData()[iter].x << "y: " << m_physics.getHeightVsDistanceData()[iter].y << "   size: " << m_physics.getHeightVsDistanceData().size()<< std::endl;
            m_ball.setPosition(newPos);
            
            iter++;
            m_clock.restart();
        }
    }
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    //states.texture = &m_tileset;

    // draw the objects
    //target.draw(m_barrelSprite, states);
    //target.draw(m_lafetSprite, states);
    if (isFly)
    {
        target.draw(m_ball, states);
    }
}
