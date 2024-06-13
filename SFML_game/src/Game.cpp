#include "Game.h"

//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(450, 750), "Pillow Catcher", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setMouseCursorVisible(false);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{

}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("res/font/font.ttf"))
	{
		std::cerr << "ERROR::GAME::Failed to load font" << std::endl;
	}

	//Init point text
	this->pointText.setPosition(20.f, 40.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	// Init game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f-150.f);

	// Init game over background
	this->gameOverBackground.setSize(sf::Vector2f(this->gameOverText.getGlobalBounds().width + 20.f, this->gameOverText.getGlobalBounds().height + 40.f));
	this->gameOverBackground.setFillColor(sf::Color::Black);
	this->gameOverBackground.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f-10.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f - 90.f);

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(250.f, 20.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
	
	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25,25,25,200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("res/gfx/Fon_igry.png"))
	{
		std::cerr << "ERROR::GAME::Failed to load background" << std::endl;
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->onHealthLoss = [&]()
	{
		this->healthLossSound.play();
	};
	this->player->setPostion(170, 600);
}

void Game::initEnemies()
{
	this->spawnTimerMax = 30.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initSounds()
{
	if (!this->healthLossBuffer.loadFromFile("res/sfx/minecraft-death-sound.wav"))
	{
		std::cerr << "������ �������� ����� ������ ��������" << std::endl;
	}
	this->healthLossSound.setBuffer(this->healthLossBuffer);

	if (!this->pointIncreaseBuffer.loadFromFile("res/sfx/sfx-5.wav"))
	{
		std::cerr << "������ �������� ����� ���������� �����" << std::endl;
	}
	this->pointIncreaseSound.setBuffer(this->pointIncreaseBuffer);
	this->pointIncreaseSound.setVolume(30); // ��������� ��������� ����� ���������� ����� (�������� �� 0 �� 100)
}

// Constructor / Destructor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();

	this->initPlayer();
	this->initEnemies();
	this->initSounds();
	this->lastRandomNumber = 0; // Initial value
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete enemies
	for (auto& i : this->enemies)
	{
		delete i;
	}
}

// Functions
unsigned Game::getPoints()
{
	return this->points;
}

int Game::generateRandomNumber(int min, int max, int lastNumber, int minDifference)
{
	int randomNumber;
	do {
		randomNumber = rand() % (max - min + 1) + min;
	} while (abs(randomNumber - lastNumber) < minDifference);
	return randomNumber;
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePoolEvents();
		if(this->player->getHp() > 0)
			this->update();

		this->render();
	}
}

void Game::updatePoolEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->player->move(-0.5f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->player->move(0.5f);
}

void Game::updateGUI()
{
	if (this->player->getHp() > 0)
	{
		std::stringstream ss;
		ss << "Points: " << this->points;
		this->pointText.setString(ss.str());

		// Update player GUI
		float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
		this->playerHpBar.setSize(sf::Vector2f(250.f * hpPercent, this->playerHpBar.getSize().y));
	}
	else
	{
		std::stringstream ss;
		ss << "Game Over!\nYour score:\n\t   " << this->points;
		this->gameOverText.setString(ss.str());

		// Update game over background size and position
		this->gameOverBackground.setSize(sf::Vector2f(this->gameOverText.getGlobalBounds().width + 40.f, this->gameOverText.getGlobalBounds().height + 40.f));
		this->gameOverBackground.setPosition(
			this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f-10.f,
			this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f-90.f);
	}
}

void Game::updateWorld()
{

}

void Game::updateCollison()
{
	//Left world collison
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPostion(0.f, this->player->getBounds().top);
	}

	//Right world colliosn
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPostion(this->window->getSize().x  - this->player->getBounds().width, this->player->getBounds().top);
	}

}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.3f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		// Assuming the range is from 0 to window width, and the minimum difference is 50
		int min = 0;
		int max = this->window->getSize().x;
		int minDifference = 160;
		int randomYPosition = generateRandomNumber(min, max, this->lastRandomNumber, minDifference);

		this->enemies.push_back(new Enemy(randomYPosition, -10.f));
		this->spawnTimer = 0.f;

		// Update the last random number
		this->lastRandomNumber = randomYPosition;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		if (enemy->getBounds().left < 0.f)
		{
			enemy->setPostion(0.f, enemy->getBounds().top);
		}
		else if (enemy->getBounds().left + enemy->getBounds().width >= this->window->getSize().x)
		{
			enemy->setPostion(this->window->getSize().x - enemy->getBounds().width, enemy->getBounds().top);
		}

		enemy->update();

		if (enemy->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
			this->player->looseHp(1);
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		if (this->enemies[i]->getBounds().intersects(this->player->getBounds()))
		{
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
			this->points++;
			//Make a sound
			this->pointIncreaseSound.play();

		}
	}
}

void Game::update()
{
	if(this->player->getHp() > 0)
	{
		this->updateInput();

		this->updateGUI();

		this->player->update();

		this->updateCollison();

		this->updateEnemies();

		this->updateCombat();
	}

	this->updateGUI();

	this->updateWorld();
}


void Game::renderGUI()
{
	if (this->player->getHp() > 0)
	{
		this->window->draw(this->pointText);
		this->window->draw(this->playerHpBarBack);
		this->window->draw(this->playerHpBar);
	}
}
void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	if (this->player->getHp() > 0)
	{
		this->renderGUI();
	}
	else
	{
		this->window->draw(this->gameOverBackground);
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}
