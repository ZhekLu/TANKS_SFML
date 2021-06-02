#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include"definecells.h"
#include"Player.h"
#include"Enemy.h"
#include"Barrier.h"

#include<fstream> /*for textures*/
#include<string>
#include<map>
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
	void updateLevelBarrierCollisions();
	void updateTanksCollision();
	void updateHitting();
	void update();
	void render();
private:
	//elements
	RenderWindow* window; 
	Player* player; 
	std::vector<Enemy*> enemies;
	std::vector<Barrier*> levelBarrier; 
	//resourses
	std::map<int, Texture> textures; 

	//fiunctions
	void initWindow();
	void initPlayer();
	void initTextures();
	void initEnemies();
	void initMap();
};

#endif // GAME_H
