#include "Game.h"
#include "Collision.h"
#include "MeleeWeapon.h"
#include "HUD.h"

Game* Game::instance_;

Game::Game()
{
	//basically the new EntityManager 
	paused_ = false;
	//camera_ = Camera();
	//player_ = Player();
	camera_.setAttachable(&player_);
	player_.setSprite(new PlayerSprite(player_.getWidth(), player_.getHeight(), getSpriteSheet("res/player.tga")));
	player_.setWeapon(new MeleeWeapon());
	player_.setX(0);
	player_.setY(200);
	hud_ = new HUD();
}

Game::~Game()
{

}

void Game::Setup()
{
	AddEntity(spawner_.createTerrain("green", 0,-20,3000,120));
	AddEntity(spawner_.createTerrain("orange", 400,150,500,150));
	AddEntity(spawner_.createTerrain("orange", 1400, 200, 400, 100));
	AddEntity(spawner_.createEnemy("basic", 1000, 120));
	AddEntity(spawner_.createItem("smallHeart", 300, 150));
}

void Game::Run(bool paused)
{
	if(!paused)
	{
		Update();
		CheckCollisions();
	}
	Draw();
}

void Game::Update()
{
	player_.updateInput();
	camera_.update();
	hud_->updateInput();

	//for(int i=0; i<terrainContainer.size(); ++i)
	//{
	//	terrainContainer[i]->updateInput();
	//}

	for(int i=0; i<enemyContainer.size(); ++i)
	{
		enemyContainer[i]->updateInput();
		if(enemyContainer[i]->getAnimState() == ANIM_STATE::DEATH)
		{
			Entity* e = enemyContainer[i];
			e->onDeath();
			enemyContainer.erase(enemyContainer.begin()+i);
			i--;
			delete e;
		}
	}

	for(int i=0; i<itemContainer.size(); ++i)
	{
		itemContainer[i]->updateInput();
		if(itemContainer[i]->getAnimState() == ANIM_STATE::DEATH)
		{
			Entity* e = itemContainer[i];
			itemContainer.erase(itemContainer.begin()+i);
			i--;
			delete e;
		}
	}
}

void Game::CheckCollisions()
{
	for(int i=0; i<terrainContainer.size(); ++i)
	{
		Collision::checkCollision(&player_, terrainContainer[i]);
		
		for(int j=0; j<enemyContainer.size(); ++j)
		{
			Collision::checkCollision(enemyContainer[j], terrainContainer[i]);
		}
	}

	for(int i=0; i<enemyContainer.size(); ++i)
	{
		Collision::checkCollision(enemyContainer[i], &player_);
	}

	for(int i=0; i<itemContainer.size(); ++i)
	{
		Collision::checkCollision(itemContainer[i], &player_);
	}
}

void Game::Draw()
{
	//maybe do a check inside of draw to see if we need to push the matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//draw stuff
	player_.draw();

	for(int i=0; i<terrainContainer.size(); ++i)
	{
		terrainContainer[i]->draw();
	}

	for(int i=0; i<enemyContainer.size(); ++i)
	{
		enemyContainer[i]->draw();
	}

	for(int i=0; i<itemContainer.size(); ++i)
	{
		itemContainer[i]->draw();
	}

	hud_->draw();

	glfwSwapBuffers();
}

void Game::Destroy()
{

}

void Game::PauseMenu()
{

}

void Game::AddEntity(Entity* e)
{
	switch(e->getEntityType())
	{
	case ENTITY_TYPE::TERRAIN:
		terrainContainer.push_back(e);
		break;
	case ENTITY_TYPE::ENEMY:
		enemyContainer.push_back(e);
		break;
	case ENTITY_TYPE::ITEM:
		itemContainer.push_back(e);
		break;
	default:
		LOGES("GAME", "Just tried to add an un-logged entity type");
		break;
	}
}

SpriteSheet* Game::getSpriteSheet(std::string filename)
{
	//do we have a copy of the desired spritesheet?
	if(spriteSheets.count(filename) > 0)
	{
		//yes? let's get it
		return spriteSheets[filename];
	}
	else
	{
		//we don't have it, so we need to create it
		const char * c = filename.c_str();
		spriteSheets[filename] = new SpriteSheet(c);
		return spriteSheets[filename];		
	}
}

