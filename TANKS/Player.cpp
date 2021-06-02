#include "Player.h"

Player::Player(Rotation rotation)
{
	//variables
	this->rotation = rotation; 
	initVariables(); 
	initTexture();
	initSprite();

	Rotate(rotation);
}

Player::~Player()
{
	for (auto* i : this->bullets)
		delete i;
}

const Vector2f& Player::getPos() const
{
	return body.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->body.getGlobalBounds();
}

bool Player::loseHp(int damage)
{
	this->hp -= damage; 
	return hp > 0;
}

void Player::setPos(float ax, float ay)
{
	this->body.setPosition(ax, ay);
}

void Player::render(RenderTarget* target)
{
	target->draw(body); 
	for (auto* bullet : this->bullets)
		bullet->render(target); 
}

void Player::update()
{
	updateAttack();
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		attackCooldown += 0.3f; 
}

const bool Player::canAttack()
{
	if (attackCooldown >= attackCooldownMax)
	{
		attackCooldown = 0.f; 
		return true; 
	}
	return false;
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

void Player::Fire()
{
	Vector2f dir(0, 0);
	switch (rotation)
	{
	case Rotation::LEFT:
		dir.x = -1.f; 
		break;
	case Rotation::UP:
		dir.y = -1.f;
		break;
	case Rotation::RIGHT:
		dir.x = 1.f; 
		break;
	case Rotation::DOWN:
		dir.y = 1.f; 
		break;
	}
	Bullet* newBullet = new Bullet(dir, this->bulletStartPos(), 4.f);
	this->bullets.push_back(newBullet); 
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

void Player::initVariables()
{
	this->attackCooldownMax = 20.f;
	this->attackCooldown = attackCooldownMax; 

	bodyHeight = 40;
	bodyWidht = 35; 

	hp = 5; 
}

const Vector2f& Player::bulletStartPos() const
{
	float displacement = (bodyWidht - bodyWidht * 3 / 16) / 2.f; // for 16x16 tank picture;
	float x = body.getPosition().x, y = body.getPosition().y; 
	switch (rotation)
	{
	case Rotation::LEFT:
		y += displacement;
		break;
	case Rotation::UP:
		x += displacement;
		break;
	case Rotation::RIGHT:
		x += bodyHeight;
		y += displacement;
		break;
	case Rotation::DOWN:
		x += displacement;
		y += bodyHeight;
		break;
	}
	return Vector2f(x, y);
}
