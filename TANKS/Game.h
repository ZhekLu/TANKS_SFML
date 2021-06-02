#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<map>
#include<iostream>
#include"definecells.h"
#include"Player.h"
#include"Enemy.h"

using namespace sf; 

class Game
{
public:
	Game();
	~Game();

	//functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateSceneCollision();
	void update();
	void render();
private:
	//elements
	RenderWindow* window; 
	Player* player; 
	std::vector<Enemy*> enemies;

	//resourses
	std::map<int, Texture*> textures; 

	//fiunctions
	void initWindow();
	void initPlayer();
	void initTextures();
	void initEnemies();
};

#endif // GAME_H
