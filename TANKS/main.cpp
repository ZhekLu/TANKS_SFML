#include "Game.h"
#include<time.h>
int main()
{
	srand(static_cast<unsigned int>(time(0)));
	bool restart = false; 
	do
	{
		Game game;
		restart = game.run();
	} while (restart);
	
	return 0; 
}