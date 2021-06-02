#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
class Enemy : public Player
{
public:
	Enemy(float speed, Rotation rotation = Rotation::DOWN);

	//variables
	bool connectWithPlayer;
	//functions
	void update() override; 
	void setCanMove(bool itis);

private:
	//variables
	bool canMove;
	float movementSpeed;

	//functions
	void initVariables() override;
	void initTexture() override;
	void initSprite() override; 
};

#endif // ENEMY_H