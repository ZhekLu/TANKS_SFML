#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
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
	void update();
	void render();
private:
	//elements
	RenderWindow* window; 
	Player* player; 

	//fiunctions
	void initWindow();
	void initPlayer();

};
#endif // !GAME_H
