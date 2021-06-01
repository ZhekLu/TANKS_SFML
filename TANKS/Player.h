#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
using namespace sf; 
#include"definecells.h"
#include"Bullet.h"

class Player
{
public:
	Player(Rotation rotation);
	~Player();
	//elements
	std::vector<Bullet*> bullets; 

	//connect
	const Vector2f& getPos() const; 
	//functions
	void render(RenderTarget *target);

	void update();
	void updateAttack();
	const bool canAttack();

	void Rotate(Rotation rotation);
	void Move(const float ax, const float ay);
	void Move(Rotation way, float step = CELL);
	void Fire();
private:
	//elements
	Sprite body;
	Texture texture; 
	//variables
	Rotation rotation; 

	int bodyHeight; 
	int bodyWidht; 
	float attackCooldown;
	float attackCooldownMax;
	//functions
	void initTexture();
	void initSprite();
	void initVariables();

	const Vector2f& bulletStartPos() const; 
};

