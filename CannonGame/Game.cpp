#include "Game.h"

Game::Game()
{
	m_window.create(sf::VideoMode(1100, 720), "Cannon Game");

	// For test
	m_testCircle.setRadius(50);
	m_testCircle.setPosition(100, 100);
	m_testCircle.setFillColor(sf::Color::Magenta);

}

void Game::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}

}

void Game::update()
{
}

void Game::render()
{
	m_window.clear();

	m_window.draw(m_testCircle);

	m_window.display();
}
