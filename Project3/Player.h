#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:


public:
	Player(void);
	~Player(void);

	void updateInput();

};



#endif
