#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"

class Weapon
{
private:

protected:
	Entity* parent;
	
	bool inUse;

	double timeStamp;

	struct HitboxData
	{
		int relativeX; //positive x is "in front of" the entity, depending on facing left or right. X val is the middle of the hitbox.
		int relativeY; //positive y is always above the entity
		int width; 
		int height;
		int delayUntilSpawn; //ms
		int lifetime; //ms
		int damage;
		bool added;
		HitboxData* next;
	};

	struct AttackData
	{
		int lifetime;
		HitboxData* hitboxes;
	};

public:
	Weapon(void);
	~Weapon(void);

	virtual void attackMid() = 0;
	virtual void attackLow() = 0;

	bool isInUse() {return inUse;}
	void setParent(Entity* p) {parent = p;}
};

#endif