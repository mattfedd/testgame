#include "DamageBox.h"

DamageBox::DamageBox(int x, int y, int width, int height) : Rect(x,y,width,height)
{
	damageAmount = 10;
}

DamageBox::~DamageBox()
{

}

int DamageBox::getDamageAmount()
{
	return damageAmount;
}

void DamageBox::setDamageAmount(int amt) 
{
	damageAmount = amt;
}