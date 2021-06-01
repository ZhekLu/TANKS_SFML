#include "Player.h"

Player::Player(Rotation rotation)
{
	this->rotation = rotation;

	initTexture();
	initSprite();
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
