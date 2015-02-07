#ifndef ENTITY_H
#define ENTITY_H

#include "Includes.h"
#include "Sprite.h"
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
	

protected:
	Sprite* sprite_;
	int width_;
	int height_;
	ENTITY_TYPE type_;
	ANIM_STATE animState;

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
	ANIM_STATE getAnimState();

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
	void setSprite(Sprite* s) {sprite_ = s;}
	void setAnimState(ANIM_STATE state) {
		animState = state;
		if (sprite_ != NULL)
			sprite_->setAnimState(state);
	}

	virtual void handleCollision(Entity* ent, CollideBox* us, CollideBox* e);

	virtual void updateInput();
	virtual void updateCollisions();
	virtual void updateGraphics();

	virtual void draw();
	virtual void debugDraw();

	void initCollideBoxes();
	std::vector<CollideBox*> getCollideBoxes() {return collideBoxes;}
	void addDamageBox(int relativeX, int relativeY, int width, int height, int lifetime, int damage);

	bool collidingTop;
	bool collidingBottom;
	bool collidingLeft;
	bool collidingRight;
};

#endif