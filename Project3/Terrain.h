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
};

#endif