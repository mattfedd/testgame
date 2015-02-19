#ifndef PLAYER_INPUT_SYSTEM_H
#define PLAYER_INPUT_SYSTEM_H

#include "System.h"

class PlayerInputSystem : public System
{
private:
	bool spaceDown;
	ALuint jumpSource, jumpBuffer;
public:
	PlayerInputSystem();
	~PlayerInputSystem();

	void update(EntityManager* em);
};

#endif