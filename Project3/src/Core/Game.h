#ifndef GAME_H
#define GAME_H

#include "Includes.h"
#include "Entity.h"
#include "Camera.h"
#include "Player.h"
#include "Spawner.h"
#include <map>

class Game
{
private:
	Game();
	void Update();
	void CheckCollisions();
	void Draw();


	Camera camera_;
	Player player_;

	Spawner spawner_;

	bool paused_;

	std::map<std::string, SpriteSheet*> spriteSheets;

	std::vector<Entity*> terrainContainer;
	std::vector<Entity*> enemyContainer;

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
	Player* getPlayer() {return &player_; }

	Spawner* getSpawner() {return &spawner_;};

	static Game* instance_;

};

#endif // GAME_H
