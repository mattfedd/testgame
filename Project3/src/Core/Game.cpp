#include "Game.h"
#include "Collision.h"
#include "MeleeWeapon.h"

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
}

Game::~Game()
{

}

void Game::Setup()
{
	AddEntity(spawner_.createTerrain("green", 0,-20,2000,120));
	AddEntity(spawner_.createTerrain("orange", 400,150,500,100));
}

void Game::Run()
{
	Update();
	CheckCollisions();
	Draw();
}

void Game::Update()
{
	player_.updateInput();
	camera_.update();

	//for(int i=0; i<terrainContainer.size(); ++i)
	//{
	//	terrainContainer[i]->updateInput();
	//}
}

void Game::CheckCollisions()
{
	for(int i=0; i<terrainContainer.size(); ++i)
	{
		Collision::checkCollision(&player_, terrainContainer[i]);
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
	default:
		LOGVS("GAME", "Just tried to add an un-logged entity type");
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

