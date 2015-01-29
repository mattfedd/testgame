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

	ATTACK_STATE attack_state;

	Weapon* weapon;

public:
	Player(void);
	~Player(void);

	void updateInput();
	void handleCollision(Entity* ent, CollideBox* us, CollideBox* e);

	void crouch();
	void uncrouch();
	void attackGroundHigh();
	void attackGroundMid();
	void attackGroundLow();

	void initCollideBoxes();

	Weapon* getWeapon();
	void setWeapon(Weapon* weapon);

	//void addDamageBox(int relativeX, int relativeY, int width, int height, int lifetime, int damage);

};



#endif
