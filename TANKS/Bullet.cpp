#include "Bullet.h"

Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float speed)
{
	body = sf::CircleShape(size);
	body.setFillColor(sf::Color(255, 255, 255));

	body.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = speed; 
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->body.getGlobalBounds();
}

void Bullet::update()
{
	body.move(movementSpeed * direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(body);
}
