#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class Bullet
{
public:
	Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float speed);
	~Bullet();
	//Connect
	const sf::FloatRect getBounds() const; 

	//Functions
	void update();
	void render(sf::RenderTarget* target);

private:
	sf::CircleShape body;
	int size = 10; 

	sf::Vector2f direction;
	float movementSpeed; 
};

