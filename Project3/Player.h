#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
	float gravity;
	bool goingUp;
	bool floating;
	float force;

public:
	Player(void);
	~Player(void);

	void updateInput();
	bool colliding;

};



#endif
