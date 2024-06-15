#include "Player.h"

//Private functions
void Player::initVariables()
{
	this->movementSpeed = 1.3f;

	this->hpMax = 3;
	this->hp = this->hpMax;
	this->movingRight = true;
}

void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("res/gfx/Podushka1.png"))
	{
		std::cerr << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << std::endl;
	}
	if (!this->textureLeft.loadFromFile("res/gfx/Podushka2.png"))
	{
		std::cerr << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << std::endl;
	}
	if (!this->textureRight.loadFromFile("res/gfx/Podushka3.png"))
	{
		std::cerr << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << std::endl;
	}

}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	//Resize the sprite
	this->sprite.scale(0.3f, 0.3f);
}

// Constructor / Destructor
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

//Accessor
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

//Modifires
void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPostion(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::looseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
	if (onHealthLoss) onHealthLoss();
}

//Functions
void Player::move(const float dirX)
{
	this->sprite.move(this->movementSpeed * dirX, 0);

	if (dirX == 0)
	{
		this->sprite.setTexture(this->texture);
		this->movingRight = false;
	}
	if (dirX > 0) {
		this->sprite.setTexture(this->textureRight);
		this->movingRight = true;
	}
	else if (dirX < 0) {
		this->sprite.setTexture(this->textureLeft);
		this->movingRight = false;
	}
}

void Player::update()
{

	float dirX = 0.f;
	float dirY = 0.f;
	bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		dirX = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		dirX = 1.f;
	}
	if (leftPressed && rightPressed)
	{
		dirX = 0.f;
	}

	this->move(dirX);
}

void Player::render(sf::RenderTarget& target) const
{
	target.draw(this->sprite);
}
