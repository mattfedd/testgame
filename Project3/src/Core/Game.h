#ifndef GAME_H
#define GAME_H

#include "Includes.h"
#include "Camera.h"
#include "Spawner.h"
#include "Tile.h"
#include <map>
#include "SpriteSystem.h"
#include "CollisionSystem.h"
#include "PlayerInputSystem.h"
#include "PhysicsSystem.h"
#include "DebugDrawSystem.h"
#include "Profiler.h"

class HUD;

struct TileWorldData
{
	float startX;
	float startY;
	int tileWidth;
	int tileHeight;
	int arrayWidth;
};

class BGSprite : public Sprite
{
public:
	BGSprite(int width, int height, SpriteSheet* ss) : Sprite(width, height, ss) 
	{
		totalFrames_ = 0;
		numAnimations_ = 0;
		sheetWidth_ = 640;
		sheetHeight_ = 360;
		frameWidth_ = 640;
		frameHeight_ = 360;

		spriteInfo_ = NULL;

		addAnimInfo(ANIM_STATE::DEFAULT, 1);
		setAnimState(ANIM_STATE::DEFAULT);
	}
	~BGSprite() {}

};

class TerrainSprite : public Sprite
{
public:
	TerrainSprite(int width, int height, SpriteSheet* ss): Sprite(width, height, ss)
	{
		totalFrames_ = 0;
		numAnimations_ = 0;
		sheetWidth_ = 512;
		sheetHeight_ = 512;
		frameWidth_ = 32;
		frameHeight_ = 32;
		frame = 0;
		animating = false;

		spriteInfo_ = NULL;
	
		addAnimInfo(ANIM_STATE::NONE, 5);
		addAnimInfo(ANIM_STATE::DEFAULT, 1);
		setAnimState(ANIM_STATE::DEFAULT);
	}
	~TerrainSprite(void) {}
};
class Game
{
private:
	Game();
	void Update();
	void CheckCollisions();
	void Draw();

	BGSprite* bg;

	Camera camera_;
	Entity* player_;
	HUD* hud_;

	EntityManager* em;

	SpriteSystem spritesys;
	CollisionSystem collisionsys;
	PlayerInputSystem playerinputsys;
	PhysicsSystem physicssys;	
	DebugDrawSystem debugdrawsys;
	
	TileWorldData tileData;

	Spawner spawner_;

	unsigned int score;

	bool paused_;

	TerrainSprite* tileReference;

	std::map<std::string, SpriteSheet*> spriteSheets;

	std::map<int, Tile*> tileIdTranslator; //an array might work just as well here

	std::vector<TextComponent*> debugTexts;

public:
	static Game* instance()
	{
		if(instance_ == NULL) instance_ = new Game();
		return instance_;
	}
	~Game();
	
	int getTileIndexByPosition(float x, float y);
	Vector2d getTilePositionByIndex(int index);

	void Setup(); //level, savestate
	void Run(bool paused);

	void Destroy();
	void PauseMenu();
	void AddEntity(Entity* e);

	void setPause(bool p) {paused_ = p;}
	bool isPaused() {return paused_;}

	SpriteSheet* getSpriteSheet(std::string filename);

	Camera* getCamera() {return &camera_; }
	Entity* getPlayer() {return player_; }

	Spawner* getSpawner() {return &spawner_;};

	static Game* instance_;
	
	TileWorldData getTileData() {return tileData;}

	unsigned int getScore() {return score; }
	void setScore(unsigned int val) {score = val;}

	void loadTiles(unsigned int level, unsigned int sublevel);

	Profiler profiler;
	std::vector<int> backgroundTiles;
	std::vector<int> foregroundTiles;
};




class TerrainOrangeSprite : public Sprite
{
public:
	TerrainOrangeSprite(int width, int height, SpriteSheet* ss): Sprite(width, height, ss)
{
	totalFrames_ = 0;
	numAnimations_ = 0;
	sheetWidth_ = 256;
	sheetHeight_ = 256;
	frameWidth_ = 64;
	frameHeight_ = 64;

	spriteInfo_ = NULL;

	addAnimInfo(ANIM_STATE::NONE, 6);	
	addAnimInfo(ANIM_STATE::DEFAULT, 1);
	setAnimState(ANIM_STATE::DEFAULT);
}
	~TerrainOrangeSprite(void) {}
};

class PlayerSprite : public Sprite
{
public:
	PlayerSprite(int width, int height, SpriteSheet* ss): Sprite(width, height, ss)
	{
		totalFrames_ = 0;
		numAnimations_ = 0;
		sheetWidth_ = 512;
		sheetHeight_ = 256;
		frameWidth_ = 64;
		frameHeight_ = 64;

		spriteInfo_ = NULL;
	
		addAnimInfo(ANIM_STATE::DEFAULT, 8);
		addAnimInfo(ANIM_STATE::STAND_MOVE, 8);
		addAnimInfo(ANIM_STATE::CROUCH, 1);

		setAnimState(ANIM_STATE::STAND_MOVE);
	}
	~PlayerSprite(void){}
};


#endif // GAME_H
