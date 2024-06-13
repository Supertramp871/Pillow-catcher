#include "Enemy.h"

void Enemy::initVariables()
{
	this->type     = 0;
	this->hpMax    = 10;
	this->hp       = 0;
	this->speed    = 3.f;
	this->damage   = 1;
	this->points   = 5;
}

void Enemy::initTexture()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Vector with filenames
	std::vector<std::string> textureFiles = {
		"res/gfx/Enemy1.png",
		"res/gfx/Enemy2.png"
	};

	// Randomize file
	int randomIndex = std::rand() % textureFiles.size();

	// Load a texture from file
	if (!texture.loadFromFile(textureFiles[randomIndex])) {
		std::cerr << "Error loading texture: " << textureFiles[randomIndex] << std::endl;
	}

}

void Enemy::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(1.5f, 1.5f);
}

// Constructor / Destructor
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

	this->sprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

//Accessors
const sf::FloatRect Enemy::getBounds() const 
{
	// Bug if be refernce
	return this->sprite.getGlobalBounds();
}

//Modifires
void Enemy::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Enemy::setPostion(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

//Functions
void Enemy::update()
{
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
