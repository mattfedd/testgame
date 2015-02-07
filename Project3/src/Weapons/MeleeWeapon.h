#ifndef MELEE_WEAPON_H
#define MELEE_WEAPON_H

#include "Weapon.h"

class MeleeWeapon : public Weapon
{
private:
	AttackData MidAttack;
	AttackData LowAttack;

	void attack(AttackData ad);

public:
	MeleeWeapon(void);
	~MeleeWeapon(void);

	virtual void attackMid();
	virtual void attackLow();
};

#endif