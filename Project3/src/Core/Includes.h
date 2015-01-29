#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <glew.h>
#include <glfw.h>
#include <math.h>
#include <vector>
#include <iterator>
#include <sstream>
#include "Logging.h"

#define GAME Game::instance()
#define GAME_TITLE "Title"

#define MAX_VECTOR_SIZE 256

/*
DONE:
	-basic collision
	-jumping
	-text
	-sideways collision
	-pausing
	-tiled textures (terrain)
	-better platforming collision
	-basic attacks/hitboxes

TODO list:
	-collision array
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
	-background/parallax
	-AI
	-sound/openAL/ogg
	-items
	-weapons/bullets
	-zones

BUGS:
	-jumping and immediately attacking makes you fly
	
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
const float ANIM_LIMITER = 10.0;  //how many game frames to wait between animation frame updates

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

enum class ATTACK_STATE
{
	NONE,
	ATTACK_LOW,
	ATTACK_MID,
	ATTACK_HIGH
};

//what animation should be playing now?
enum class ANIM_STATE
{
	BIRTH,				//plays when creating object, not always necessary
	DEATH,				//plays when object dies
	DEFAULT,			//normal animation, generally for objects with one or zero animations
	STATIONARY,	//standing still	
	IDLE,			//standing still for a while
	LOOK,			//looking functionality
	LOOK_UP,
	LOOK_DOWN,
	LOOK_AROUND,		//can be randomly called for variety in idle animation
	PUSH,			//push against walls, boxes, et
	GROUND_MOVE,	//movement
	GROUND_MOVE_UP,		//ladder
	GROUND_MOVE_DOWN,
	WALL_CLIMB,	//climbing sideways, not a ladder
	WALL_HANG,		//hanging
	AIR_MOVE,		//air movement
	AIR_MOVE_UP,	//for any ascension, including jumping
	AIR_MOVE_DOWN,	//any falling
	ATTACK,		//attacks
	ATTACK_UP,
	ATTACK_DOWN,
	HURT,			//getting hurt
	RECOIL,		//recoil for whatever reason
	UPGRADE,		//good things happening
	CROUCH
};

//entitties
enum class ENTITY_TYPE
{
	PLAYER,
	ENEMY,
	TERRAIN,
	BULLET,
	ENVIRONMENT,
	ENTITY

	//to be filled out further...
};

enum class DIRECTION
{
	RIGHT, 
	LEFT
};


#endif
