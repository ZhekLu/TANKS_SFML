#include "Game.h"

//Ctor/Des
Game::Game()
{
	initWindow();
	initTextures();
	initGUI();
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
bool Game::run()
{
	while (window->isOpen())
	{
		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
				this->window->close();
			if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
				window->close();
			if (e.type == Event::KeyPressed && e.key.code == Keyboard::R)
			{
				window->close();
				return 1;
			}
		}
		if(!gameIsOver && !missionCompleted)
			this->update();
		this->render();
	}
	return 0;
}

//void Game::updatePollEvents()
//{
//	Event e;
//	while (window->pollEvent(e))
//	{
//		if (e.type == Event::Closed)
//			this->window->close();
//		if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
//			window->close();
//		if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter)
//		{
//			window->close();
//		}
//	}
//}

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

	if (Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->player->canAttack())
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
		if (!deleted && bullet->getBounds().intersects(eagle.getGlobalBounds()))
		{
			gameIsOver = true; 
			delete player->bullets.at(counter);
			player->bullets.erase(player->bullets.begin() + counter);
			deleted = true;
			counter--;
		}
		counter++; 
	}

	//enemies
	for (auto* enemy : enemies)
	{
		counter = 0;
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
			if (!deleted && bullet->getBounds().intersects(eagle.getGlobalBounds()))
			{
				gameIsOver = true;
				delete enemy->bullets.at(counter);
				enemy->bullets.erase(enemy->bullets.begin() + counter);
				deleted = true;
				counter--;
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
	//for eagle;
	if (player->getBounds().intersects(eagle.getGlobalBounds()))
		player->Move(-2.f);
	for (auto* e : enemies)
		if (e->getBounds().intersects(eagle.getGlobalBounds()))
			e->setCanMove(false);
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

void Game::updateEnemiesCollision()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int k = i + 1; k < enemies.size(); k++)
		{
			if (enemies[i]->getPos().y > CELL * 4 && enemies[i]->getBounds().intersects(enemies[k]->getBounds()))
			{
				enemies[i]->setCanMove(false);
				enemies[k]->setCanMove(false);
			}
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
					enemiesQuantity--;
					enemiesQuantityKilled++; 
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
					gameIsOver = true; 
				}
			}
		}
	}

}

void Game::updateEnemies()
{
	static int i = 0;
	spawnEnemyTimer++;
	if (spawnEnemyTimer >= spawnEnemyTimerMax && enemiesQuantity < 5) /*there*/
	{
		Enemy* newE = new Enemy(spawnPoints[i], 1.f);
		enemies.push_back(newE);
		spawnEnemyTimer = 0;
		enemiesQuantity++; 
		i++;
		if (i > 6)
			i = 0;
	}
}

void Game::updateGUI()
{
}

void Game::update()
{
	//system
	updateGUI();
	//player
	updateInput();
	updateSceneCollision();
	updateLevelBarrierCollisions();
	updateTanksCollision();
	player->update();

	//enemies
	updateEnemies();
	for (auto* e : enemies)
		e->update();
	updateEnemiesCollision();
	//e&p
	updateBullets();
	updateHitting();
}

void Game::renderGUI()
{
	window->draw(widgetGUI);
	for (int i = 0, rows = 0; i < enemiesQuantityMax - enemiesQuantityKilled; i ++)
	{
		if (!(i % 2))
		{
			widgetEnemy.setPosition(30 + WIDTH, rows * CELL * 2);
			window->draw(widgetEnemy);
		}
		if (i % 2)
		{
			widgetEnemy.setPosition(WIDTH + 55, rows * CELL * 2);
			window->draw(widgetEnemy);
			rows++;
		}
	}
	window->draw(flag);
	lifeCountText.setString(String(std::to_string(player->getHp()))); 
	window->draw(lifeCountText);
}

void Game::render()
{
	window->clear();

	renderGUI();

	for (auto* b : levelBarrier)
		b->render(window);

	window->draw(eagle);

	player->render(window);

	for (auto* enemy : enemies)
		enemy->render(window);
	if (gameIsOver)
	{
		gameEndText.setString("Game over!");
		gameEndText.setPosition(WIDTH / 2 - gameEndText.getGlobalBounds().width / 2.f,
			HEIGHT / 2 - gameEndText.getGlobalBounds().height / 2.f);
		window->draw(gameEndText);
	}
	if (missionCompleted)
	{
		gameEndText.setString("WIN!");
		gameEndText.setPosition(WIDTH / 2 - gameEndText.getGlobalBounds().width / 2.f,
			HEIGHT / 2 - gameEndText.getGlobalBounds().height / 2.f);
		window->draw(gameEndText);
	}

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
	if (!textures[7].loadFromFile("resourses/eagle40px.png"))
		std::cout << "ERROR::LOAD::TEXTURE::GAME::resourses/eagle40px.png" << std::endl;
	if (!textures[Barrier::BRICK].loadFromFile("resourses/brickBlock40px.png"))
		std::cout << "ERROR::LOAD::TEXTURE::GAME::resourses/brickBlock40px.png" << std::endl; 
	if (!textures[Barrier::IRON].loadFromFile("resourses/ironBlock40px.png"))
		std::cout << "ERROR::LOAD::TEXTURE::GAME::resourses/ironBlock40px.png" << std::endl;
	if (!textures[20].loadFromFile("resourses/currEQuantitu.png"))
		std::cout << "ERROR::LOAD::TEXTURE::GAME::resourses/currEQuantitu.png" << std::endl;
	if(!textures[8].loadFromFile("resourses/flag.png"))
		std::cout << "ERROR::LOAD::TEXTURE::GAME::resourses/flag.png" << std::endl;
	//forFlag.createMaskFromColor(Color(76, 80, 76));
	//textures[8].loadFromImage(forFlag);
		
}

void Game::initEnemies()
{
	spawnEnemyTimerMax = 300;
	spawnEnemyTimer = spawnEnemyTimerMax;

	enemiesQuantity = 0;
	enemiesQuantityKilled = 0;
	enemiesQuantityMax = 20;

	spawnPoints[0] = Vector2f(0, 0);
	spawnPoints[6] = Vector2f(WIDTH - 35, 0);
	spawnPoints[2] = Vector2f(10 * CELL, 0);
	spawnPoints[5] = Vector2f(WIDTH - 10 * CELL - 35, 0);
	spawnPoints[3] = Vector2f(18 * CELL, 0);
	spawnPoints[4] = Vector2f(WIDTH - 18 * CELL - 35, 0);
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
					else if (str[i] == 'e')
					{
						eagle.setTexture(textures[7]);
						eagle.setPosition(displacement, rows * 2 * CELL);
						displacement += 4 * CELL;
						i += 2; 
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

void Game::initGUI()
{
	//GAME OVER txt
	if (!font.loadFromFile("resourses/PixellettersFull.ttf"))
		std::cout << "ERROR::LOAD::FONT::GAME::resourses/PixellettersFull.ttf" << std::endl;
	gameEndText.setFont(font);
	gameEndText.setCharacterSize(70);
	gameEndText.setFillColor(Color::White);

	widgetGUI.setSize(Vector2f(8 * CELL, HEIGHT));
	widgetGUI.setFillColor(Color(93, 96, 90));
	widgetGUI.setPosition(WIDTH, 0);

	widgetEnemy.setTexture(textures[20]);
	
	flag.setTexture(textures[8]);
	flag.setPosition(WIDTH + 10, 40 * CELL);

	lifeCountText.setFont(font);
	lifeCountText.setCharacterSize(40);
	lifeCountText.setFillColor(Color::White);
	lifeCountText.setPosition(WIDTH + 40, 42 * CELL);
	//gameEndText.setString("Game over!");
	/*gameEndText.setPosition(WIDTH / 2- gameEndText.getGlobalBounds().width / 2.f,
		HEIGHT / 2 - gameEndText.getGlobalBounds().height / 2.f);*/

}
