#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Includes.h"
#include "Sprite.h"

struct Component
{
	Component() : valid(false) {}
	Component(bool v) : valid(v) {}
	bool getValid() {return valid;}
	bool valid;
};

struct PositionComponent : Component
{
	PositionComponent() : x(0), y(0), z(0), Component(false) {}
	PositionComponent(float x_, float y_, float z_) : x(x_), y(y_), z(z_),Component(true) {}

	static unsigned int getId() { return POSITION_ID; }

	float x;
	float y;
	float z;
};

struct VelocityComponent : Component
{
	VelocityComponent() : dx(0), dy(0), Component(false) {}
	VelocityComponent(float x, float y) : dx(x), dy(y), Component(false) {}

	static unsigned int getId() { return VELOCITY_ID; }

	float dx;
	float dy;
};

struct HealthComponent : Component
{
	HealthComponent() : health(0), maxHealth(0), Component(false) {}
	HealthComponent(int h, int m) : health(h), maxHealth(m), Component(false) {}

	static unsigned int getId() { return HEALTH_ID; }

	int health; 
	int maxHealth;
};


struct SpriteComponent : Component
{
	SpriteComponent() : Component(false) {};
	SpriteComponent(std::string name_, Sprite s) : name(name_), sprite(s), Component(true) {}

	static unsigned int getId() { return SPRITE_ID; }

	std::string name;
	Sprite sprite;
};



//struct CollideBoxEdge 
//{
//	float x1;
//	float x2;
//	float y1;
//	float y2;
//
//	//dx and dy triggers basically tell you which side of the object this edge is
//	float dxTolerance; //dx must be less/greater than this value to trigger
//	float dyTolerance; //dy must be less/greater than this value to trigger
//};
//
//struct CollideBox
//{
//	float x;
//	float y;
//	CollideBoxEdge left;
//	CollideBoxEdge right;
//	CollideBoxEdge top;
//	CollideBoxEdge bottom;
//};
//
//struct PhysicsComponent : Component
//{
//	float ddx;
//	float ddy;
//	bool isOnGround;
//	CollideBox AABB;
//
//};

#endif