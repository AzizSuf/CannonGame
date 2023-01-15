#include "Game.h"

Game::Game()
{
	m_window.create(sf::VideoMode(1280, 720), "Cannon Game");

	// For test
	m_testCircle.setRadius(50);
	m_testCircle.setPosition(100, 100);
	m_testCircle.setFillColor(sf::Color::Magenta);

	// for test
	//m_cannon.setPosition(0, 580);

	if (!m_backgroungTexture.loadFromFile("Resources/Backgroung.png"))
	{

	}

	m_backgroungSprite.setTexture(m_backgroungTexture);
	m_backgroungSprite.move(0, -300);
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

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				m_cannon.moveBarrel(-3);
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				m_cannon.moveBarrel(3);
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				m_cannon.debugDump();
			}
		}

#if 1
		if (event.type == sf::Event::MouseMoved)
		{
			std::cout << "x: " << sf::Mouse::getPosition(m_window).x << "  y: " << sf::Mouse::getPosition(m_window).y << std::endl;

			m_cannon.aimBarrelToPoint(sf::Mouse::getPosition(m_window));

		}
#endif
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "!!! Fire !!!" << std::endl;
				m_cannon.fire();
			}
		}
	}

}

void Game::update()
{
	m_cannon.update(sf::Time());
}

void Game::render()
{
	m_window.clear();

	//m_window.draw(m_testCircle);
	m_window.draw(m_backgroungSprite);
	m_window.draw(m_cannon);

	m_window.display();
}
