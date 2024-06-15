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
	// Enums
	enum class GameState { MENU, INFO, PLAYING, EXIT };

	// Variables
	bool isGameOver;
	GameState state;
	int selectedItem;

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

	// Menu
	sf::Text menu[3];
	sf::Sprite backgroundMenu;
	sf::Sprite backgroundInfo;
	sf::SoundBuffer navigateSoundBuffer;
	sf::Sound navigateSound;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	sf::Texture backgroundMenuTexture;
	sf::Texture backgroundInfoTexture;


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
	void initMenu();
	void processMenuEvents();
	void processInfoEvents();
	void renderMenu();
	void renderInfo();

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
