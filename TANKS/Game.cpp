#include "Game.h"

//Ctor/Des
Game::Game()
{
	initWindow();
	initPlayer();
}

Game::~Game()
{
	delete player;
	delete window;
}

//functions
void Game::run()
{
	while (window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::update()
{
	Event e;
	while (window->pollEvent(e))
	{
		if (e.type == Event::Closed)
			this->window->close();
		if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
			window->close();
	}
	
}

void Game::render()
{
	window->clear();

	player->render(window);

	window->display();
}

//private functions
void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(WIDTH + 8 * CELL, HEIGHT), "The best course work in the World", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	player = new Player();
}
