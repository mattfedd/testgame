#ifndef ENTITY_H
#define ENTITY_H

#include "Includes.h"
#include "Sprite.h"
#include "Game.h"
#include "CollideBox.h"
#include "DamageBox.h"
#include <vector>

class Entity
{
private:
	int x_; //pixel-based position (x,y,z)
	int y_;
	int z_;
	int maxSpeed_;
	float dx_;
	float dy_;
	float ddx_;
	float ddy_;
	
	bool airState;	//true = airborne, false = ground
	int actionState; //0,1,2,3,4,5 = stand, walk, jump, crouch, crouch-walk, use item, interact

protected:
	Sprite* sprite_;
	int width_;
	int height_;
	ENTITY_TYPE type_;

	std::vector<CollideBox*> collideBoxes;
	std::vector<DamageBox*> damageBoxes;

public:
	Entity(void);
	~Entity(void);

	float getXNorm();
	float getYNorm();
	float getZNorm();
	int getX();
	int getY();
	int getZ();
	float getDX();
	float getDY();
	float getDDX();
	float getDDY();
	int getWidth();
	int getHeight();
	int getMaxSpeed();
	ENTITY_TYPE getEntityType();

	void setPosition(int x, int y, int z);
	void setX(int x);
	void setY(int y);
	void setZ(int z);
	void setDX(float dx);
	void setDY(float dy);
	void setDDX(float ddx);
	void setDDY(float ddy);
	void setWidth(int w);
	void setHeight(int h);
	void setSize(int width, int height);
	void setMaxSpeed(int val);
	void setEntityType(ENTITY_TYPE type);

	virtual void handleCollision(Entity* ent);

	virtual void updateInput();
	virtual void updateCollisions();
	virtual void updateGraphics();

	virtual void draw();

	void initCollideBoxes();
	void addDamageBox(int relativeX, int relativeY, int width, int height, int lifetime, int damage);

	bool collidingTop;
	bool collidingBottom;
	bool collidingLeft;
	bool collidingRight;
};

#endif