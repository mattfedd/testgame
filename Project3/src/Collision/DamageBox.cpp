#include "DamageBox.h"

DamageBox::DamageBox(int x, int y, int width, int height) : Rect(x,y,width,height)
{
	damageAmount = 10;
	useLifeTime = false;
	lifetime = 0;
	dead = false;
	spawnTime = glfwGetTime();
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

void DamageBox::setLifeTime(int t)
{
	if (t==0)
	{
		dead = true;
		lifetime = 0;
		return;
	}

	useLifeTime = true;
	lifetime = t;
	dead = false;
}

void DamageBox::update()
{
	if(useLifeTime)
	{
		if((glfwGetTime() - spawnTime)*1000 > lifetime)
		{
			dead = true;
		}
	}
}