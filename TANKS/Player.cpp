#include "Player.h"

Player::Player(Rotation rotation)
{
	//variables
	this->rotation = rotation; 

	initTexture();
	initSprite();

	Rotate(rotation);
}

Player::~Player()
{
}

void Player::render(RenderTarget* target)
{
	target->draw(body); 
}

void Player::update()
{
}

void Player::Rotate(Rotation rotation)
{
	this->rotation = rotation;
	switch (rotation)
	{
	case Rotation::LEFT:
		body.setTextureRect(IntRect(0, 0, 40, 35));
		break;
	case Rotation::UP:
		body.setTextureRect(IntRect(5, 35, 35, 40));
		break; 
	case Rotation::RIGHT:
		body.setTextureRect(IntRect(40, 0, 40, 35));
		break; 
	case Rotation::DOWN:
		body.setTextureRect(IntRect(40, 35, 35, 40));
		break;
	}
}

void Player::Move(const float ax, const float ay)
{
	float movementSpeed = 1.f;
	body.move(ax * movementSpeed, ay * movementSpeed); 
}

void Player::Move(Rotation way, float step)
{
	Rotate(way);
	switch (rotation)
	{
	case Rotation::LEFT:
		body.move(-step, 0);
		break;
	case Rotation::UP:
		body.move(0, -step);
		break;
	case Rotation::RIGHT:
		body.move(step, 0);
		break;
	case Rotation::DOWN:
		body.move(0, step);
		break;
	}
}

void Player::initTexture()
{
	if (!texture.loadFromFile("resourses/playerTileset.png"))
		std::cout << "ERR::LOADFROMFILE::resourses/playerTileset.png" << std::endl;
}

void Player::initSprite()
{
	body.setTexture(this->texture);
}
