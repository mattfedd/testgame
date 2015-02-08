#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
class Item : public Entity
{
private:


public:
	Item(void);
	~Item(void);

	virtual void onCollect();
	virtual void updateInput();
	virtual void handleCollision(Entity* ent, CollideBox* us, CollideBox* e);
	virtual void initCollisionBoxes();
};

class HealthPickupItem : public Item
{
private:
	unsigned int healthRestored;
public:
	HealthPickupItem(unsigned int amount);
	~HealthPickupItem();

	void onCollect();
	void initCollisionBoxes();
};

class HealthPickupItemSprite : public Sprite
{
private:

public:
	HealthPickupItemSprite(int width, int height, SpriteSheet* ss);
	~HealthPickupItemSprite();
};

#endif