#include "Game.h"

Game::Game() :
	rd(), gen(rd()), distr(500, 1100)
{
	m_window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), "Cannon Game", sf::Style::Titlebar|sf::Style::Close);
	//m_window.setSize(sf::Vector2u(W_WIDTH, W_HEIGHT));
	//m_window.setFramerateLimit(120);
	m_window.setVerticalSyncEnabled(true);

	//m_view = m_window.getDefaultView();

	// For test
	//m_testCircle.setRadius(50);
	//m_testCircle.setPosition(100, 100);
	//m_testCircle.setFillColor(sf::Color::Magenta);

	//if (!m_backgroungTexture.loadFromFile("Resources/Backgroung.png"))
	//{

	//}
	m_backgroungSprite.setTexture(ResourceHolder::getTexture("Backgroung.png"));
	m_backgroungSprite.move(0, -300);


	m_fireTexture.create(200, 200);
	m_fireSprite.setTexture(m_fireTexture);

	if (!sf::Shader::isAvailable())
	{
		std::cerr << "Shader are not available" << std::endl;
	}

	// Set the resolution parameter (the resoltion is divided to make the fire smaller)
	m_fireShader.setParameter("resolution", sf::Vector2f(1280 / 2, 720 / 2));

	if (!m_font.loadFromFile("Resources/arial.ttf"))
	{

	}
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(25);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setString("Score: 0");
	m_scoreText.setPosition(20, 20);

	// test
	Box box;

	m_boxes.push_back(box);
}

void Game::run()
{
	m_shaderClock.restart();

	while (m_window.isOpen())
	{
		processEvents();
		update();
		checkCollisions();
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

		if (event.type == sf::Event::Resized)
		{
			m_view.setSize({ static_cast<float>(event.size.width),static_cast<float>(event.size.height) });
			m_window.setView(m_view);
		}

		switch (m_gameState)
		{
		case Game::GameState::MainMenuOpened:
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_gameState = GameState::Playing;
					m_mainMenu.hide();
				}
			}
			break;
		case Game::GameState::Playing:
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					m_cannon.moveBarrel(-3);
					m_mainMenu.moveUp();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					m_cannon.moveBarrel(3);
					m_mainMenu.moveDown();
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					m_cannon.debugDump();
				}

				if (event.key.code == sf::Keyboard::Escape)
				{
					m_gameState = GameState::MainMenuOpened;
					m_mainMenu.show();
					/*
					m_mainMenu.toggle();
					if (m_mainMenu.getState() == MainMenu::State::Shown)
					{
						// = GameState::MainMenuOpened;
					}
					else
					{
						//m_gameState = GameState::Playing;
					}*/
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				//std::cout << "x: " << sf::Mouse::getPosition(m_window).x << "  y: " << sf::Mouse::getPosition(m_window).y << std::endl;
				m_cannon.aimBarrelToPoint(sf::Mouse::getPosition(m_window));
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//std::cout << "!!! Fire !!!" << std::endl;
					m_projectiles.push_back(Projectile());
					m_cannon.fire(m_projectiles.back());
				}
			}
			break;
		case Game::GameState::Paused:
			break;
		default:
			break;
		}
		
	}
}

void Game::update()
{
	//if (m_gameState == GameState::Playing)
	//{
		m_cannon.update(sf::Time());

		for (auto& pr : m_projectiles)
		{
			pr.update();
		}
    //}
	// test
	if (m_animateClock.getElapsedTime().asMilliseconds() > 100)
	{
		//if (m_boxes[0].getPosition().y > 800)
		//m_boxes[0].move(1)
	}

	if (m_spawnBoxesClock.getElapsedTime().asMilliseconds() > 1000)
	{
		spawnBoxes();
		m_spawnBoxesClock.restart();
	}

	if (m_moveBoxesClock.getElapsedTime().asMilliseconds() > 50)
	{
		std::uniform_int_distribution<> distr(1, 5);
		for (auto& box : m_boxes)
		{
			box.move(sf::Vector2f(0, distr(rd)));
		}
		m_moveBoxesClock.restart();
	}
}

void Game::render()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	m_fireShader.setParameter("mouse", sf::Vector2f(mousePos.x, mousePos.y - 720 / 2));

	m_window.clear();
	//m_window.draw(m_testCircle);
	m_window.draw(m_backgroungSprite);

	for (auto& pr : m_projectiles)
	{
		m_window.draw(pr);
	}

	m_window.draw(m_cannon);

	for (auto& box : m_boxes)
	{
		m_window.draw(box);
	}

	m_window.draw(m_mainMenu);
	m_window.draw(m_scoreText);
	m_window.display();
}

void Game::updateScore(int score)
{
	m_scoreText.setString("Score: " + std::to_string(score));
	m_score = score;
}

void Game::spawnBoxes()
{
	Box box;
	box.setPosition(sf::Vector2f(distr(gen), 0));
	m_boxes.push_back(std::move(box));
}

void Game::checkCollisions()
{
	bool isHit = false;

	for (size_t i = 0; i < m_boxes.size(); i++)
	{
		if (!m_boxes[i].isAlive())
		{
			m_boxes.erase(m_boxes.begin() + i);
		}
	}

	for (size_t i = 0; i < m_projectiles.size(); i++)
	{
		if (!m_projectiles[i].isAlive())
		{
			m_projectiles.erase(m_projectiles.begin() + i);
		}
	}

	for (auto& box : m_boxes)
	{
		for (auto& pr : m_projectiles)
		{
			sf::FloatRect projectileRect = pr.getGlobalBounds();
			sf::FloatRect boxRect = box.getGlobalBounds();

			sf::FloatRect screenRect(sf::Vector2f(0, 0), sf::Vector2f(1280, 720));

			if (boxRect.intersects(projectileRect))
			{
				// std::cout << "HIT" << std::endl;
				box.destroy();
				updateScore(m_score + 1);

			}
			//std::cout << box.getPosition().y << std::endl;
			if (!screenRect.intersects(projectileRect))
			{
				// std::cout << "Projectile out of screen. DESTROYED" << std::endl;
				pr.explode();
			}
		}

		// Destroy box when its underfloor
		if (box.getPosition().y > W_HEIGHT)
		{
			box.destroy();
			updateScore(m_score - 1);
		}
	}

	//std::cout << boxRect.left << std::endl;
}
