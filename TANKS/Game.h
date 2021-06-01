#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<map>
#include"definecells.h"
#include"Player.h"
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
	void update();
	void render();
private:
	//elements
	RenderWindow* window; 
	Player* player; 
	//resourses
	std::map<int, Texture*> textures; 
	//fiunctions
	void initWindow();
	void initPlayer();
	void initTextures();
};
#endif // !GAME_H
