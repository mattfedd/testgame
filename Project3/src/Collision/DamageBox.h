#ifndef DAMAGE_BOX_H
#define DAMAGE_BOX_H

#include "Rect.h"

class Entity;

class DamageBox : public Rect
{
private:
	int damageAmount;
	int lifetime;
	bool useLifeTime;
	bool dead;
	double spawnTime;

	std::vector<Entity*> hitEntities;

public:
	DamageBox(int x, int y, int width, int height);
	~DamageBox();

	int getDamageAmount();
	void setDamageAmount(int amount);

	void update();
	bool isDead() { return dead;}
	void setLifeTime(int lifetime);

	void addHitEntity(Entity* e);
	std::vector<Entity*> getHitEntities(){return hitEntities;}
	bool isInHitEntities(Entity* e);

};

#endif