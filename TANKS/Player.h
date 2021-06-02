#ifndef PLAYER_H
#define PLAYER_H

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
	const sf::FloatRect getBounds() const;
	const Rotation getRotation() const;

	bool loseHp(int damage = 1);
	void setPos(float ax, float ay);
	//functions
	void render(RenderTarget *target);

	virtual void update();
	void updateAttack();
	const bool canAttack();

	void Rotate(Rotation rotation);
	void Move(const float ax, const float ay);
	void Move(Rotation way, float step = CELL);
	void Move(float step = CELL);

	void Fire();
protected:
	//ctor for Enemy class
	Player(){}
	//elements
	Sprite body;
	Texture texture; 
	//variables
	Rotation rotation; 
	int hp;

	int bodyHeight; 
	int bodyWidht; 
	float attackCooldown;
	float attackCooldownMax;
	//functions
	virtual void initTexture();
	virtual void initSprite();
	virtual void initVariables();

	const Vector2f& bulletStartPos() const; 
};

#endif //PLAYER_H
