#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
private:

public:
	Weapon(void);
	~Weapon(void);

	virtual void attackMid() = 0;
	virtual void attackLow() = 0;
	virtual void attackHigh() = 0;
};

#endif