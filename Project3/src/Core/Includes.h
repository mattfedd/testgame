#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <glew.h>
#include <glfw.h>
#include <math.h>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include "Logging.h"
#include "alut.h"

#define GAME Game::instance()
#define GAME_TITLE "Title"

#define MAX_VECTOR_SIZE 256

/*
Time to redo this list

Current work:
	Entity Component System
		Collision System DONE (for the world+entity collision at least)
		Physics System
		Player Input System + States
		Animation System from States
	Tile based world

Coming up:
	Rename "Entity" to "Entity" DONE

	Using components...
	-Remake HUD
	-Remake heart drops
	-Remake enemy
	-Remake attacks

	Reading level data from files, making tiles and entities on the fly
	Defining new tiles and entities from files alone

	Creating more entities/assets (art stuff)

	Particles

	Interaction effects
	-switch weapon
	-transition to new screen/level
	-talk

	Text interaction model (Textboxes, scrolling, creating/loading text, responses, state-based text)

	Weapon sprites that attach to entities

	Toggles (F1-12) for various controls
		Debug draw
		Full level reset
		Zoom in/out
		Display framerate, cpu stats
		Display player component data

	Mouse recognition/support

	In game level editor

	Sound (OpenAL/ALUT)

	Menu 
	-Adjustable display properties
	-Adjustable audio properties
	
*/


const int SCREEN_WIDTH = 1080/2;
const int SCREEN_HEIGHT = 720/2;
const int Z_CAP = 100;
const float FRAME_RATE = 60.0;
const float ANIM_LIMITER = 4.0;  //how many game frames to wait between animation frame updates

const int COLLIDE_MAX = 10;
const int HBOX_MAX = 10;
const int IBOX_MAX = 10;

const int NUM_COMPONENTS = 16;
const int CONTAINER_SIZE = 1024;

const int NUM_TILES = 512;


struct Vector2d
{
	int x;
	int y;
};

struct ColorRGB
{
	ColorRGB(char r, char g, char b) : R(r), G(g), B(b) {}
	ColorRGB() {}
	char R;
	char G;
	char B;
};

enum COLLISION_GROUPS : unsigned int
{
	COLLISION_PLAYER = 1,
	COLLISION_WORLD = 1<<1,
	COLLISION_ENEMY = 1<<2,
	COLLISION_PLAYERBULLET = 1<<3,
	COLLISION_ENEMYBULLET = 1<<4,
	COLLISION_INTERACTABLE = 1<<5,
	COLLISION_ITEM = 1<<6,
	COLLISION_ZONE = 1<<7
};

enum COMPONENT_ID : unsigned int
{
	POSITION_ID = 0,
	VELOCITY_ID,
	HEALTH_ID,
	SPRITE_ID,
	STATE_ID,
	WEAPON_ID,
	INTERACTABLE_ID,
	TEXT_ID,
	DEATH_TIMER_ID,
	COLLISION_ID,
	GRAVITY_ID,
	PHYSICS_ID
};

enum class COLLIDING_SIDE
{
	NONE,
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
};

//what's under the entity?
//used to be able to bind the Entity's base speed with whatever's under it
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
	INVULNERABLE,		//whenever the Entity has been hit, it is invulnerable for a short period before allowing another hit to register
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
	SPAWN,				//plays when creating Entity, not always necessary
	DEATH,				//plays when Entity dies
	DEFAULT,			//normal animation, generally for Entitys with one or zero animations	
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
