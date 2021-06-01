#include "Enemy.h"

Enemy::Enemy(float speed, Rotation rotation) : Player(rotation)
{
	canMove = false; 
	movementSpeed = speed;
	connectWithPlayer = false; 
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
