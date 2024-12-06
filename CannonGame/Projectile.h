#pragma once
#include <SFML/Graphics.hpp>
#include "utils.h"
#include "ThrowPhysics.h"


class Projectile : public sf::Drawable, public sf::Transformable
{

public:
	Projectile();

	void launch(double angle);
	void explode();
	bool isAlive() const;
	void setInitialPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds();

	sf::Vector2f convertPhysicModelToScreenCoords(sf::Vector2f physicPos);
	sf::Vector2f convertScreenToPhysicModelCoords(sf::Vector2f screenPos);

public:
	void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::CircleShape m_ball;
	sf::Clock m_clock;

	double m_flyAngle;

	bool isFly = false;

	ThrowPhysics m_physics;

	bool m_isAlive = true;

	// TODO:
	int iter;
};

