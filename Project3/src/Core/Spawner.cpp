#include "Spawner.h"
#include "Game.h"

Spawner::Spawner(void)
{
}


Spawner::~Spawner(void)
{
}


Terrain* Spawner::createTerrain(std::string id, int x, int y, int width, int height)
{
	Terrain* t = new Terrain();
	t->setX(x);
	t->setY(y);
	t->setWidth(width);
	t->setHeight(height);

	if(id.compare("green") == 0)
	{
		t->setSprite(new TerrainGreenSprite(width, height, GAME->getSpriteSheet("res/terrain.tga")));
	}
	else if(id.compare("orange") == 0)
	{
		t->setSprite(new TerrainOrangeSprite(width, height, GAME->getSpriteSheet("res/terrain.tga")));
	}

	return t;
}