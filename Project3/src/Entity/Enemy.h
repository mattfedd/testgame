#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Weapon.h"

class Enemy : public Entity
{
private:
	Weapon* weapon;
public:
	Enemy();
	~Enemy();

	void updateInput();

	void initCollisionBoxes();
	void handleCollision(Entity* ent, CollideBox* us, CollideBox* e);
	Weapon* getWeapon();
	void setWeapon(Weapon* weapon);
};

class EnemyBasicSprite : public Sprite
{
public:
	EnemyBasicSprite(int width, int height, SpriteSheet* ss);
	~EnemyBasicSprite();
};



#endif