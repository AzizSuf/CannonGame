#pragma once

#include <SFML/Graphics.hpp>
#include "Cannon.h"
#include "Projectile.h"
#include "Box.h"
#include "MainMenu.h"
#include "ResourceHolder.h"
#include <random>

constexpr auto W_WIDTH = 1280;
constexpr auto W_HEIGHT = 720;


class Game : public sf::NonCopyable
{
	enum class GameState
	{
		MainMenuOpened,
		Playing,
		Paused
	};

public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

private:
	void updateScore(int score);
	void spawnBoxes();
	void checkCollisions();

private:
	sf::RenderWindow m_window;
	sf::View m_view;
	sf::CircleShape m_testCircle;
	//sf::Texture& m_backgroungTexture;
	sf::Sprite m_backgroungSprite;

	// General ojbects ------------
	sf::Font m_font;
	sf::Text m_scoreText;
	int m_score = 0;

	Cannon m_cannon;
	std::vector<Box> m_boxes;

	std::vector<Projectile> m_projectiles;

	MainMenu m_mainMenu;

	// ----------------------------


	// Shader test
	sf::Shader m_fireShader;
	sf::Texture m_fireTexture;
	sf::Sprite m_fireSprite;
	sf::Clock m_shaderClock;

	GameState m_gameState = GameState::Playing;
	sf::Clock m_clock;
	sf::Clock m_animateClock;
	sf::Clock m_spawnBoxesClock;
	sf::Clock m_moveBoxesClock;

	std::random_device rd;                 // obtain a random number from hardware
	std::mt19937 gen;                      // seed the generator
	std::uniform_int_distribution<> distr; // define the range
};

