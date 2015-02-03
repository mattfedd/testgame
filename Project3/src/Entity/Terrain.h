#ifndef TERRAIN_H
#define TERRAIN_H

#include "entity.h"

class Terrain :	public Entity
{
private:

public:
	Terrain(void);
	~Terrain(void);

	virtual void draw();
	virtual void debugDraw();
};

class TerrainGreenSprite : public Sprite
{
public:
	TerrainGreenSprite(int width, int height, SpriteSheet* ss);
	~TerrainGreenSprite(void);
};

class TerrainOrangeSprite : public Sprite
{
public:
	TerrainOrangeSprite(int width, int height, SpriteSheet* ss);
	~TerrainOrangeSprite(void);
};

#endif