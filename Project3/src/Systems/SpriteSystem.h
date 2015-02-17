#ifndef SPRITE_SYSTEM_H
#define SPRITE_SYSTEM_H

//#include "Components.h"
#include "System.h"

class SpriteSystem : public System
{
public:
	SpriteSystem();
	~SpriteSystem();

	void update(EntityManager* em); //AKA draw()
};

#endif