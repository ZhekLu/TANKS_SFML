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
		rotation = Rotation(rand() % 4);
		canMove = true; 
	}
	this->Move(rotation, movementSpeed);
}

void Enemy::setCanMove(bool itis)
{
	canMove = itis;
}

void Enemy::initVariables()
{
	attackCooldownMax = 20.f;
	attackCooldown = attackCooldownMax;

	bodyHeight = 40;
	bodyWidht = 35;

	hp = 3;
}

void Enemy::initTexture()
{
	if (!texture.loadFromFile("resourses/enemyTileset.png"))
		std::cout << "ERR::LOADFROMFILE::resourses/playerTileset.png" << std::endl;
}

void Enemy::initSprite()
{
	body.setTexture(this->texture);
	body.setPosition(13 * CELL + 2, 0);
}
