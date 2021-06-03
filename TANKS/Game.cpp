#include "Game.h"

//Ctor/Des
Game::Game()
{
	initWindow();
	initTextures();
	initMap();
	initPlayer();
	initEnemies();
}

Game::~Game()
{
	delete player;
	delete window;

	//if Texture*
	//for (auto& t : this->textures)
	//	delete t.second; 
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
		bool deleted = false; 
		if (bullet->getBounds().top < 0.f || bullet->getBounds().top >= HEIGHT
			|| bullet->getBounds().left < 0.f || bullet->getBounds().left >= WIDTH)
		{	
			delete player->bullets.at(counter);
			player->bullets.erase(player->bullets.begin() + counter);
			deleted = true; 
			counter--;
		}
		if (!deleted)
		{
			int brCounter = 0;
			for (auto* br : levelBarrier)
			{
				if (!deleted && bullet->getBounds().intersects(br->getBounds()))
				{
					if (!br->loseHp(bullet->getRotation()))
					{
						delete levelBarrier.at(brCounter);
						levelBarrier.erase(levelBarrier.begin() + brCounter);
						brCounter--;
					}

					delete player->bullets.at(counter);
					player->bullets.erase(player->bullets.begin() + counter);
					deleted = true;
					counter--;
				}
				brCounter++;
			}
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
			bool deleted = false; 
			if (bullet->getBounds().top < 0.f || bullet->getBounds().top >= HEIGHT
				|| bullet->getBounds().left < 0.f || bullet->getBounds().left >= WIDTH)
			{
				delete enemy->bullets.at(counter);
				enemy->bullets.erase(enemy->bullets.begin() + counter);
				deleted = true;
				counter--;
			}
			if (!deleted)
			{
				int brCounter = 0;
				for (auto* br : levelBarrier)
				{
					if (!deleted && bullet->getBounds().intersects(br->getBounds()))
					{
						if (!br->loseHp(bullet->getRotation()))
						{
							delete levelBarrier.at(brCounter);
							levelBarrier.erase(levelBarrier.begin() + brCounter);
							brCounter--;
						}
						delete enemy->bullets.at(counter);
						enemy->bullets.erase(enemy->bullets.begin() + counter);
						deleted = true; 
						counter--;

					}
					brCounter++; 
				}
			}
			counter++;
		}
	}
}

void Game::updateSceneCollision()
{
	//player

	/*left & right*/
	if (player->getPos().x < 0.f)
		player->setPos(0.f, player->getPos().y);
	else if (player->getPos().x + player->getBounds().width > WIDTH)
		player->setPos(WIDTH - player->getBounds().width, player->getPos().y);
	/*up & down*/
	if (player->getPos().y < 0.f)
		player->setPos(player->getPos().x, 0.f);
	else if (player->getPos().y + player->getBounds().height > HEIGHT)
		player->setPos(player->getPos().x, HEIGHT - player->getBounds().height);

	//enemy
	for (auto* enemy : enemies)
	{
		/*left & right*/
		if (enemy->getPos().x < 0.f)
		{
			enemy->setPos(0.f, enemy->getPos().y);
			enemy->setCanMove(false);
		}
		else if (enemy->getPos().x + enemy->getBounds().width > WIDTH)
		{
			enemy->setPos(WIDTH - enemy->getBounds().width, enemy->getPos().y);
			enemy->setCanMove(false);
		}
		/*up & down*/
		if (enemy->getPos().y < 0.f)
		{
			enemy->setPos(enemy->getPos().x, 0.f);
			enemy->setCanMove(false);
		}
		else if (enemy->getPos().y + enemy->getBounds().height > HEIGHT)
		{
			enemy->setPos(enemy->getPos().x, HEIGHT - enemy->getBounds().height);
			enemy->setCanMove(false);
		}
	}
}

void Game::updateLevelBarrierCollisions()
{
	for (auto* br : levelBarrier)
	{
		//player
		if (player->getBounds().intersects(br->getBounds()))
			player->Move(-2.f);

		//enemies
		for (auto* e : enemies)
			if (e->getBounds().intersects(br->getBounds()))
				e->setCanMove(false);
	}
}

void Game::updateTanksCollision()
{
	for (auto* enemy : enemies)
	{
		if (player->getBounds().intersects(enemy->getBounds()))
		{
			if (abs(player->getRotation() - enemy->getRotation()) == 2)
			{
				player->Move(-2.f);
				enemy->connectWithPlayer = true;
				break;
			}
			else
			{
				switch (player->getRotation())
				{
				case LEFT:
					if(player->getPos().x + 2.f >= enemy->getPos().x + enemy->getBounds().width)
						player->Move(-2.f);
					break;
				case UP:
					if (player->getPos().y + 2.f >= enemy->getPos().y + enemy->getBounds().height)
						player->Move(-2.f);
					break;
				case RIGHT:
					if (player->getPos().x + player->getBounds().width <= enemy->getPos().x + 2.f)
						player->Move(-2.f);
					break;
				case DOWN:
					if (player->getPos().y + player->getBounds().height <= enemy->getPos().y + 2.f)
						player->Move(-2.f);
					break;
				}
			}
			enemy->setCanMove(false);
			
		}
	}
}

void Game::updateHitting()
{
	for (int e = 0; e < enemies.size(); e++)
	{
		bool deleted = false; 
		// player -> enemies
		for (int b = 0; !deleted && b < player->bullets.size(); b++)
		{
			if (enemies[e]->getBounds().intersects(player->bullets[b]->getBounds()))
			{
				delete player->bullets[b];
				player->bullets.erase(player->bullets.begin() + b);
				b--; 

				if (!enemies[e]->loseHp())
				{
					//std::cout << "killed" << std::endl; 
					deleted = true; 
					delete enemies[e];
					enemies.erase(enemies.begin() + e);
					e--;
					
				}
			}
		}
		// enemies -> player
		for (int b = 0; !deleted && b < enemies[e]->bullets.size(); b++)
		{
			if (player->getBounds().intersects(enemies[e]->bullets[b]->getBounds()))
			{
				delete enemies[e]->bullets[b];
				enemies[e]->bullets.erase(enemies[e]->bullets.begin() + b);
				b--;

				if (!player->loseHp())
				{
					//std::cout << "U are killed" << std::endl;
				}
			}
		}
	}

}

void Game::update()
{
	//system
	updatePollEvents();

	//player
	updateInput();
	updateSceneCollision();
	updateLevelBarrierCollisions();
	updateTanksCollision();
	player->update();

	//enemies
	for (auto* e : enemies)
		e->update();
	//e&p
	updateBullets();
	updateHitting();
}

void Game::render()
{
	window->clear();

	for (auto* b : levelBarrier)
		b->render(window);

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
	if (!textures[Barrier::BRICK].loadFromFile("resourses/brickBlock40px.png"))
		std::cout << "ERROR::LOAD::TEXTURE::GAME::resourses/brickBlock40px.png" << std::endl; 
	if (!textures[Barrier::IRON].loadFromFile("resourses/ironBlock40px.png"))
		std::cout << "ERROR::LOAD::TEXTURE::GAME::resourses/ironBlock40px.png" << std::endl;
}

void Game::initEnemies()
{
	Enemy* newE = new Enemy(1.f);
	enemies.push_back(newE);
}

void Game::initMap()
{
	std::ifstream level("resourses/level1.txt");
	if (level.is_open())
	{
		std::string str;
		int rows = 0; 

		Barrier* newIt;
		while (getline(level, str))
		{
			int displacement = 0;
			if(str.length() > 5)
				for (int i = 0; i < str.length() && i < WIDTH / (CELL * 2);)
				{
					if (str[i] == '0')
					{
						displacement += 2 * CELL;
						i++;
					}
					else
					{
						if((str[i] - '0') % 2)
							newIt = new Barrier(displacement, rows * 2 * CELL, str[i] - '0', textures[Barrier::IRON]);
						else 
							newIt = new Barrier(displacement, rows * 2 * CELL, str[i] - '0', textures[Barrier::BRICK]);
						levelBarrier.push_back(newIt);
						switch (str[i])
						{
						case '1':
						case '2':
						case '5':
						case '6':
							i += 2;
							displacement += 4 * CELL;
							break;
						case '3':
						case '4':
							i++; 
							displacement += 2 * CELL;
							break;
						}
					}
				}
			rows++;
		}
		level.close();
	}
	else
	{
		std::cout << "ERROR::LOAD::LEVEL::GAME::resourses/level1.txt" << std::endl; 
	}
}
