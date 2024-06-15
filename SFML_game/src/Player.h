#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <functional>

class Player
{
private:
	// Variables
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture textureRight;
	sf::Texture textureLeft;

	float movementSpeed;

	int hp;
	int hpMax;

	// Animation variables
	bool movingRight;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	// Constructor / Destructor
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	sf::FloatRect getBounds() const;
	const int& getHp()  const;
	const int& getHpMax()  const;

	//Modifires
	void setPosition(const sf::Vector2f pos);
	void setPostion(const float x, const float y);
	void setHp(const int hp);
	void looseHp(const int value);

	//Functions
	void move(const float dirX);

	void update();
	void render(sf::RenderTarget& target) const;

	// Signal for health loss
	std::function<void()> onHealthLoss;
};

