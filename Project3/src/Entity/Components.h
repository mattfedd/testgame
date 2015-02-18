#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Includes.h"
#include "Sprite.h"
#include "TextSprite.h"

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
	PositionComponent(int x_, int y_, int z_=0) : x(x_), y(y_), z(z_),Component(true) {}

	static unsigned int getId() { return POSITION_ID; }

	int x;
	int y;
	int z;
};

struct VelocityComponent : Component
{
	VelocityComponent() : dx(0), dy(0), maxSpeed(0), Component(false) {}
	VelocityComponent(float x, float y, float max = 30) : dx(x), dy(y), maxSpeed(max), Component(false) {}

	static unsigned int getId() { return VELOCITY_ID; }

	float dx;
	float dy;
	float maxSpeed;
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
	SpriteComponent() : Component(false) {}
	SpriteComponent(std::string name_, Sprite s) : name(name_), sprite(s), Component(true) {}

	static unsigned int getId() { return SPRITE_ID; }

	std::string name;
	Sprite sprite;
};

struct TextComponent : Component
{
	TextComponent() : Component(false) {}
	TextComponent(std::string words, TextSprite* ts, int x=0, int y=0, float size = 24.0, ColorRGB color = ColorRGB(0xff,0xff,0xff)) : text(words), sprite(ts), offsetX(x), offsetY(y), textSize(size), textColor(color) {}
	
	static unsigned int getId() { return TEXT_ID; }

	std::string text;
	ColorRGB textColor;
	float textSize;
	int offsetX; //the reference is always a PositionComponent
	int offsetY;
	TextSprite* sprite;
	//int charsPerLine; //how many chars to write until a new line
};

struct CollideBoxEdge 
{
	CollideBoxEdge() {}
	CollideBoxEdge(float x, float y, float xx, float yy, float dx = 0, float dy = 0) : x1(x), x2(xx), y1(y), y2(yy), dxTolerance(dx), dyTolerance(dy) {}

	float x1;
	float x2;
	float y1;
	float y2;

	//dx and dy triggers basically tell you which side of the object this edge is
	float dxTolerance; //dx must be less/greater than this value to trigger
	float dyTolerance; //dy must be less/greater than this value to trigger
};

struct CollideBox
{
	CollideBox() {}
	CollideBox(float x_, float y_, int width, int height): x(x_), y(y_) 
	{
		left = CollideBoxEdge(x_, y_, x_, y_+height);
		right = CollideBoxEdge(x_+width, y_, x_+width, y_+height);
		top = CollideBoxEdge(x_, y_+height, x_+width, y_+height);
		bottom = CollideBoxEdge(x_, y_, x_+width, y_);
	}

	//x and y reference from the bottom left edge of the entity (aka the position component)
	//true position in the world is the position component + this position 
	float x;
	float y;
	CollideBoxEdge left;
	CollideBoxEdge right;
	CollideBoxEdge top;
	CollideBoxEdge bottom;
};


struct CollisionComponent : Component
{
	CollisionComponent() : Component(false) {}
	CollisionComponent(CollideBox box, int group, int mask) : AABB(box), collisionGroup(group), collisionMask(mask), Component(true){}

	static unsigned int getId() {return COLLISION_ID;}

	//General world collision box
	CollideBox AABB;

	//what group of things does this belong to?
	int collisionGroup;

	//what is it allowed to collide with?
	int collisionMask;

	//what is it colliding with now?
	int isCollidingMask;
};

struct PhysicsComponent : Component
{
	PhysicsComponent(bool gravity = true) : useGravity(gravity), dx(0), dy(0), ddx(0), ddy(0), gravity(0), maxSpeed(10), Component(true) {}

	static unsigned int getId() {return PHYSICS_ID; }

	bool useGravity;

	//some forces
	float gravity; 
	float wind;
	float friction;

	float dx;
	float dy;
	int maxSpeed;

	float ddx; 
	float ddy;
};

struct StateComponent : Component
{
	bool isInAir; //or isOnGround; for the opposite
	bool isAttacking;
	bool direction;
	bool isAlive;

	int inputState;
};


#endif