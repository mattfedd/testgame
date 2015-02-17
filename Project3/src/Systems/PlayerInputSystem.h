#ifndef PLAYER_INPUT_SYSTEM_H
#define PLAYER_INPUT_SYSTEM_H

#include "System.h"

class PlayerInputSystem : public System
{
public:
	PlayerInputSystem();
	~PlayerInputSystem();

	void update(EntityManager* em);
};

#endif