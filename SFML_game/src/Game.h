#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <map>

#include "Player.h"
#include "Enemy.h"

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	// Variables
	bool isGameOver;

	// Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	int lastRandomNumber;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;
	sf::Text pointsOverText;

	sf::RectangleShape gameOverBackground;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;

	// Sound
	sf::SoundBuffer healthLossBuffer;
	sf::Sound healthLossSound;
	sf::SoundBuffer pointIncreaseBuffer;
	sf::Sound pointIncreaseSound;

	// Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();
	void initSounds();

public:
	// Constructor / Destructor
	Game();
	virtual ~Game();

	// Functions
	unsigned getPoints();
	int generateRandomNumber(int min, int max, int lastNumber, int minDifference);
	void run();
	void restartGame();
	void updatePoolEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollison();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};

