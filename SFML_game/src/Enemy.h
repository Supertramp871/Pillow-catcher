#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Enemy
{
private:
	//Variables
	sf::Sprite sprite;
	sf::Texture texture;
	
	int type;
	int hpMax;
	int hp;
	float speed;
	int damage;
	int points;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	// Constructor / Destructor
	Enemy(float pos_x, float posy);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;

	//Modifires
	void setPosition(const sf::Vector2f pos);
	void setPostion(const float x, const float y);

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

