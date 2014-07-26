#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <glew.h>
#include <glfw.h>
#include <math.h>
#include <vector>
#include <iterator>
#include <sstream>

#define GAME Game::instance()
#define GAME_TITLE "Title"

/*
DONE:
	-basic collision
	-jumping
	-text

TODO list:
	-collision array
	-sideways collision
	-terrain/map/level objects
	-more advanced collision (interpolation, corners, one way collision)
	-HUD for health etc
	-game states and transitions
	-death, pause, non-input states and corresponding triggers/transitions
	-background/parallax
	-particles (rain, dirt, sparks, ambient float, 
	-enemy/sprite
	-menu screen + manager
	-level objects
	-particles
	-background/parallax
	-pausing
	-AI
	-sound/openAL/ogg
	-items
	-weapons/bullets
	-zones
*/


struct Vert
{
	int x;
	int y;
	Vert* next;
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int Z_CAP = 100;
const float FRAME_RATE = 60.0;
const float ANIM_LIMITER = 20.0;  //how many game frames to wait between animation frame updates

const int COLLIDE_MAX = 10;

const int HBOX_MAX = 10;

enum class COLLIDING_SIDE
{
	NONE,
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
};

//what's under the entity?
//used to be able to bind the object's base speed with whatever's under it
enum class ENTITY_UNDER
{
	AIR,
	STILL_PLATFORM_1WAY,
	STILL_PLATFORM_2WAY,
	MOVE_PLATFORM_1WAY,
	MOVE_PLATFORM_2WAY
};

//status of entity
enum class ENTITY_STATUS
{
	NORMAL,
	INVULNERABLE,		//whenever the object has been hit, it is invulnerable for a short period before allowing another hit to register
	DEAD
};

//what animation should be playing now?
enum class ANIM_STATE
{
	BIRTH,				//plays when creating object, not always necessary
	DEATH,				//plays when object dies
	DEFAULT,			//normal animation, generally for objects with one or zero animations
	STATIONARY_LEFT,	//standing still
	STATIONARY_RIGHT,	
	IDLE_LEFT,			//standing still for a while
	IDLE_RIGHT,
	LOOK_LEFT,			//looking functionality
	LOOK_RIGHT,
	LOOK_UP_LEFT,
	LOOK_UP_RIGHT,
	LOOK_DOWN_LEFT,
	LOOK_DOWN_RIGHT,
	LOOK_AROUND,		//can be randomly called for variety in idle animation
	PUSH_LEFT,			//push against walls, boxes, etc
	PUSH_RIGHT,
	GROUND_MOVE_LEFT,	//movement
	GROUND_MOVE_RIGHT,
	GROUND_MOVE_UP,		//ladder
	GROUND_MOVE_DOWN,
	WALL_CLIMB_LEFT,	//climbing sideways, not a ladder
	WALL_CLIMB_RIGHT,
	WALL_HANG_LEFT,		//hanging
	WALL_HANG_RIGHT,	//also for sliding down walls
	AIR_MOVE_LEFT,		//air movement
	AIR_MOVE_RIGHT,
	AIR_MOVE_UP_LEFT,	//for any ascension, including jumping
	AIR_MOVE_UP_RIGHT,
	AIR_MOVE_DOWN_LEFT,	//any falling
	AIR_MOVE_DOWN_RIGHT,
	ATTACK_LEFT,		//attacks
	ATTACK_RIGHT,
	ATTACK_UP_LEFT,
	ATTACK_UP_RIGHT,
	ATTACK_DOWN_LEFT,
	ATTACK_DOWN_RIGHT,
	HURT_LEFT,			//getting hurt
	HURT_RIGHT,
	RECOIL_LEFT,		//recoil for whatever reason
	RECOIL_RIGHT,
	UPGRADE_LEFT,		//good things happening
	UPGRADE_RIGHT
};

//entitties
enum class ENTITIES
{
	PLAYER,
	ENEMY
	//to be filled out further...
};

#endif
