#pragma once

#include <SFML/Graphics.hpp>
#include "Cannon.h"

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

private:
	sf::RenderWindow m_window;
	sf::CircleShape m_testCircle;
	sf::Texture m_backgroungTexture;
	sf::Sprite m_backgroungSprite;

	Cannon m_cannon;

	sf::Clock m_clock;

};

