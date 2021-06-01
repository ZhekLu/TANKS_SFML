#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
using namespace sf; 
#include "definecells.h"
class Player
{
public:
	Player(Rotation rotation);
	~Player();

	//functions
	void render(RenderTarget *target);
	void update();
	void Rotate(Rotation rotation);
	void Move(const float ax, const float ay);
	void Move(Rotation way, float step = CELL);
private:
	//elements
	Sprite body;
	Texture texture; 
	//variables
	Rotation rotation; 
	//functions
	void initTexture();
	void initSprite();
};

