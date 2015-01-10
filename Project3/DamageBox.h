#ifndef DAMAGE_BOX_H
#define DAMAGE_BOX_H

#include "Rect.h"

class DamageBox : public Rect
{
private:
	int damageAmount;

public:
	DamageBox(int x, int y, int width, int height);
	~DamageBox();

	int getDamageAmount();
	void setDamageAmount(int amount);

};

#endif