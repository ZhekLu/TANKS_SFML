#include "Bullet.h"

Bullet::Bullet( sf::Vector2f direction, sf::Vector2f startPos, float speed)
{
	//body
	body = sf::CircleShape(size / 2);
	body.setFillColor(sf::Color(255, 255, 255));
	body.setPosition(startPos);

	//movement direction
	this->direction = direction; 
	movementSpeed = speed; 
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
	body.move(direction * movementSpeed); 
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(body);
}
