#include "EntityManager.h"
#include "Terrain.h"
#include "Collision.h"

EntityManager::EntityManager()
{
	player = NULL;
}

EntityManager::~EntityManager()
{
	if(player != NULL)
	{
		delete player;
		player = NULL;
	}

	for (int i=0; i<terrain.size(); ++i)
	{
		if(terrain[i] != NULL)
		{
			delete terrain[i];
			terrain[i] = NULL;
		}
	}
}

void EntityManager::addPlayer(int x, int y)
{
	if (player != NULL)
	{
		delete player;
	}

	player = new Player();
	player->setX(x);
	player->setY(y);

	GAME->getCamera()->setAttachable(player);
}

void EntityManager::addTerrain(int x, int y, int width, int height)
{
	if (terrain.size() > MAX_VECTOR_SIZE)
	{
		LOGES(__FUNCTION__, "Too many cooks in terrain array");
		return;
	}

	Terrain* t = new Terrain();
	t->setX(x);
	t->setY(y);
	t->setWidth(width);
	t->setHeight(height);
	
	terrain.push_back(t);
}

void EntityManager::checkAllCollisions()
{
	for(int i=0; i<terrain.size(); ++i)
	{
		Collision::checkCollision(player, terrain[i]);
	}
}

void EntityManager::drawAllEntities()
{
	for(int i=0; i<terrain.size(); ++i)
	{
		terrain[i]->draw();
	}

	player->draw();
}