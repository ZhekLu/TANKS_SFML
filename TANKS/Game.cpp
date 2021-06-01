#include "Game.h"

//Ctor/Des
Game::Game()
{
	initWindow();
	initTextures();
	initPlayer();
	initEnemies();
}

Game::~Game()
{
	delete player;
	delete window;

	for (auto& t : this->textures)
		delete t.second; 
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

void Game::updatePollEvents()
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

void Game::updateInput()
{
	//Move player

	if (Keyboard::isKeyPressed(sf::Keyboard::A))
		player->Move(Rotation::LEFT, 2.f);
	else if (Keyboard::isKeyPressed(sf::Keyboard::W))
		player->Move(Rotation::UP, 2.f);
	else if (Keyboard::isKeyPressed(sf::Keyboard::D))
		player->Move(Rotation::RIGHT, 2.f);
	else if (Keyboard::isKeyPressed(sf::Keyboard::S))
		player->Move(Rotation::DOWN, 2.f);

	if (Keyboard::isKeyPressed(sf::Keyboard::C) && this->player->canAttack())
		player->Fire();
	//Another Way
	//if(Keyboard::isKeyPressed(sf::Keyboard::A))
	//	player->Move(-1.f, 0.f);
	//if(Keyboard::isKeyPressed(sf::Keyboard::W))
	//	player->Move(0.f, -1.f);
	//if (Keyboard::isKeyPressed(sf::Keyboard::D))
	//	player->Move(1.f, 0.f);
	//if (Keyboard::isKeyPressed(sf::Keyboard::S))
	//	player->Move(0.f, 1.f);
}

void Game::updateBullets()
{
	//player
	unsigned short counter = 0; 
	for (auto* bullet : player->bullets)
	{
		bullet->update();

		if (bullet->getBounds().top < 0.f || bullet->getBounds().top >= HEIGHT
			|| bullet->getBounds().left < 0.f || bullet->getBounds().left >= WIDTH)
		{	
			delete player->bullets.at(counter);
			player->bullets.erase(player->bullets.begin() + counter);
			counter--;
		}
		counter++; 
	}
	//enemies
	counter = 0;
	for (auto* enemy : enemies)
	{
		for (auto* bullet : enemy->bullets)
		{
			bullet->update();

			if (bullet->getBounds().top < 0.f || bullet->getBounds().top >= HEIGHT
				|| bullet->getBounds().left < 0.f || bullet->getBounds().left >= WIDTH)
			{
				delete enemy->bullets.at(counter);
				enemy->bullets.erase(enemy->bullets.begin() + counter);
				counter--;
			}
			counter++;
		}
	}
}

void Game::update()
{
	//system
	updatePollEvents();

	//player
	updateInput();
	player->update();

	//enemies
	for (auto* e : enemies)
		e->update();
	updateBullets();
}

void Game::render()
{
	window->clear();

	player->render(window);
	for (auto* enemy : enemies)
		enemy->render(window);

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
	player = new Player(Rotation::DOWN);
}

void Game::initTextures()
{
	this->textures[1] = new Texture();
	this->textures[1]->loadFromFile("resourses/ironBlock40px");
}

void Game::initEnemies()
{
	Enemy* newE = new Enemy(1.f);
	enemies.push_back(newE);
}
