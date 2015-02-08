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
	-collision array
	-more advanced collision (interpolation, corners, one way collision)

TODO list:
	-terrain/map/level objects
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
	-collidingTop triggers on bottom colliding box when both are active - need a way to get topmost one and check that only?
	
NOTES:
	-sprite class could benefit from some container, like the way spritesheet works. Might not be good to allocate a new one for every object.

TODO
	-fix character control/movement (done)
	-add health and death (done ish)
	-add invulnerable boxes (done ish)
	-add items
	-add interaction
	-add textboxes
	-improve animations and attacks
	-add weapon with new animations and hitboxes...
	
	-redo terrain objects to have more customizable terrain options
		-top edge textures
		-left edge textures
		-right edge textures
		-middle randomize pool
		-etc

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
const int IBOX_MAX = 10;

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
	NONE,
	SPAWN,				//plays when creating object, not always necessary
	DEATH,				//plays when object dies
	DEFAULT,			//normal animation, generally for objects with one or zero animations	
	IDLE1,			//standing still for a while
	IDLE2,
	PUSH,			//push against walls, boxes, et
	STAND_MOVE,		//movement
	CROUCH_MOVE,
	CLIMB,			//ladder
	AIR_MOVE_UP,	//for air ascension, including jumping
	AIR_MOVE_DOWN,	//any falling
	CROUCH_AIR_MOVE_UP,
	CROUCH_AIR_MOVE_DOWN,
	GROUND_ATTACK,		//attacks
	GROUND_CROUCH_ATTACK,
	AIR_ATTACK,
	AIR_ATTACK_DOWN,
	GROUND_MAGIC,
	AIR_MAGIC,
	CROUCH_MAGIC,
	DAMAGED,			//getting hurt
	UPGRADE,		//good things happening
	CROUCH,
	VICTORY
};

//entitties
enum class ENTITY_TYPE
{
	STATIC_BG,
	PARALLAX_BG_A,
	PARALLAX_BG_B,
	ITEM,
	ENEMY,
	TERRAIN,
	NPC,
	PLAYER,
	BULLET,
	LIGHT_BEAM,
	FOREGOUND,
	HUD,
	TEXTBOX,
	PAUSE_MENU_BG,
	PAUSE_MENU_CONTENT,
	PAUSE_MENU_TOP,
	ENTITY
};

enum class DIRECTION
{
	RIGHT, 
	LEFT
};


#endif
