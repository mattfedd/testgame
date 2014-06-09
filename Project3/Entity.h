#ifndef ENTITY_H
#define ENTITY_H

#include "Includes.h"
#include "Sprite.h"
#include "Game.h"

class Entity
{
private:
	int x_; //pixel-based position (x,y,z)
	int y_;
	int z_;
	int width_;
	int height_;
	int maxSpeed_;
	float dx_;
	float dy_;
	float ddx_;
	float ddy_;
	
	bool airState;	//true = airborne, false = ground
	int actionState; //0,1,2,3,4,5 = stand, walk, jump, crouch, crouch-walk, use item, interact

	Sprite* sprite_;

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
	//long getRadiusSquared();

	void setPosition(int x, int y, int z);
	void setX(int x);
	void setY(int y);
	void setZ(int z);
	void setDX(float dx);
	void setDY(float dy);
	void setDDX(float ddx);
	void setDDY(float ddy);
	void setSize(int width, int height);
	void setMaxSpeed(int val);
	//void setRadiusSquared(long val);

	virtual void updateInput();
	virtual void updateCollisions();
	virtual void updateGraphics();

	void draw();
};



#endif