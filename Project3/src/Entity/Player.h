#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Weapon.h"

class Player : public Entity
{
private:
	float gravity;
	bool goingUp;
	bool floating;
	float force;

	Weapon* weapon;

public:
	Player(void);
	~Player(void);

	void updateInput();
	void handleCollision(Entity* e);

	void crouch();
	void uncrouch();
	void attackGroundHigh();
	void attackGroundMid();
	void attackGroundLow();

	void initCollideBoxes();

};



#endif
