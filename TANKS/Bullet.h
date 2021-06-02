#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include"definecells.h"

class Bullet
{
public:
	Bullet(sf::Vector2f direction, sf::Vector2f startPos, float speed);
	~Bullet();
	//Connect
	const sf::FloatRect getBounds() const; 
	const Rotation getRotation() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);

private:
	sf::CircleShape body;
	int size = 10; 

	sf::Vector2f direction;
	float movementSpeed;
};

#endif //BULLET_H
