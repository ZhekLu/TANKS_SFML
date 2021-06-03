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
	bool run();

	//void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateSceneCollision();
	void updateLevelBarrierCollisions();
	void updateTanksCollision();
	void updateEnemiesCollision();
	void updateHitting();
	void updateEnemies();
	void updateGUI();
	void update();
	void renderGUI();
	void render();
private:
	//variables - system
	bool gameIsOver = false; 
	bool missionCompleted = false;

	int enemiesQuantity;
	int enemiesQuantityKilled;
	int enemiesQuantityMax;
	
	int spawnEnemyTimer;
	int spawnEnemyTimerMax;
	Vector2f spawnPoints[7];

	//elements
	RenderWindow* window; 
	Player* player; 
	std::vector<Enemy*> enemies;
	std::vector<Barrier*> levelBarrier; 
	Sprite eagle; 
	//resourses
	std::map<int, Texture> textures; 

	//GUI
	Font font; 
	Text gameEndText;
	Text lifeCountText;
	sf::RectangleShape widgetGUI;
	Sprite widgetEnemy; 
	Sprite flag; 

	//fiunctions
	void initWindow();
	void initPlayer();
	void initTextures();
	void initEnemies();
	void initMap();
	void initGUI();
};

#endif // GAME_H
