#include "Enemy.h"

Enemy::Enemy(float speed, Rotation rotation) : Player()
{
	//variables
	canMove = false;
	movementSpeed = speed;
	connectWithPlayer = false;
	this->rotation = rotation;

	// init part from Player;
	initVariables();
	initTexture();
	initSprite();

	Rotate(rotation);
}

void Enemy::update()
{
	updateAttack();
	if (canAttack())
		this->Fire();
	if (connectWithPlayer)
	{
		connectWithPlayer = false; 
		return; 
	}
	if (!canMove)
	{
		//rotation = 
		canMove = true; 
	}
	this->Move(rotation, movementSpeed);
}

void Enemy::setCanMove(bool itis)
{
	canMove = itis;
}

void Enemy::initTexture()
{
	if (!texture.loadFromFile("resourses/enemyTileset.png"))
		std::cout << "ERR::LOADFROMFILE::resourses/playerTileset.png" << std::endl;
}
