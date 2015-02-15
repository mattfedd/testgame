#ifndef SPRITE_SYSTEM_H
#define SPRITE_SYSTEM_H

//#include "Components.h"
#include "EntityManager.h"

class SpriteSystem
{
public:
	SpriteSystem();
	~SpriteSystem();

	void update(EntityManager* em); //AKA draw()
};

#endif