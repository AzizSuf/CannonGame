#include "Box.h"

Box::Box()
{
	m_boxSprite.setTexture(ResourceHolder::getTexture("wooden_box.png"));

	m_boxSprite.setPosition(1000, 350);
	m_boxSprite.setScale(0.6, 0.6);
}

sf::FloatRect Box::getGlobalBounds()
{
	// std::cout << "box: " << m_boxSprite.getGlobalBounds().left;
	return m_boxSprite.getGlobalBounds();
}

void Box::setPosition(sf::Vector2f pos)
{
	m_boxSprite.setPosition(pos);
}

sf::Vector2f Box::getPosition()
{
	return m_boxSprite.getPosition();
}

void Box::move(sf::Vector2f delta)
{
	m_boxSprite.move(delta);
}

void Box::destroy()
{
	m_boxSprite.setTexture(ResourceHolder::getTexture("wooden_box_destroyed.png"));
	m_isAlive = false;
}

bool Box::isAlive()
{
	return m_isAlive;
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();
	target.draw(m_boxSprite, states);
}
