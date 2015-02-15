#ifndef GAME_H
#define GAME_H

#include "Includes.h"
#include "Camera.h"
#include "Spawner.h"
#include "Tile.h"
#include <map>
#include "SpriteSystem.h"

class HUD;

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

class Game
{
private:
	Game();
	void Update();
	void CheckCollisions();
	void Draw();

	BGSprite* bg;

	Camera camera_;
	Object* player_;
	HUD* hud_;

	EntityManager* em;
	SpriteSystem spritesys;

	Spawner spawner_;

	bool paused_;

	std::map<std::string, SpriteSheet*> spriteSheets;

	//template <typename T>
	//struct Container {
	//	Container() {};
	//	void add(T item) {};
	//	void get(int index) {};
	//	T items[256]; 
	//};

	//Container<Entity> entities;
	//Container<Component> components[2];

	//Container<HealthComponent> tempArray;
	//Container<PositionComponent> posArray;

	int tiles[256]; 	
	std::map<int, Tile*> tileIdTranslator; //an array might work just as well here

public:
	static Game* instance()
	{
		if(instance_ == NULL) instance_ = new Game();
		return instance_;
	}
	~Game();

	void Setup(); //level, savestate
	void Run(bool paused);

	void Destroy();
	void PauseMenu();
	void AddEntity(Entity* e);

	void setPause(bool p) {paused_ = p;}
	bool isPaused() {return paused_;}

	SpriteSheet* getSpriteSheet(std::string filename);

	Camera* getCamera() {return &camera_; }
	Object* getPlayer() {return player_; }

	Spawner* getSpawner() {return &spawner_;};

	static Game* instance_;

};


class TerrainGreenSprite : public Sprite
{
public:
	TerrainGreenSprite(int width, int height, SpriteSheet* ss): Sprite(width, height, ss)
	{
		totalFrames_ = 0;
		numAnimations_ = 0;
		sheetWidth_ = 256;
		sheetHeight_ = 256;
		frameWidth_ = 64;
		frameHeight_ = 64;

		spriteInfo_ = NULL;
	
		addAnimInfo(ANIM_STATE::DEFAULT, 1);
		setAnimState(ANIM_STATE::DEFAULT);
	}
	~TerrainGreenSprite(void) {}
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

	addAnimInfo(ANIM_STATE::NONE, 1);	
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
