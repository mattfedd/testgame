#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Includes.h"
#include "Entity.h"
#include "Player.h"

class EntityManager 
{
private:
	Player* player;
	std::vector<Entity*> terrain;
	//std::vector<Entity*> enemies;
	//std::vector<Entity*> textBoxes;

public:
	EntityManager(void);
	~EntityManager(void);

	void addPlayer(int x, int y);
	Player* getPlayer() { return player; }
	void addTerrain(int x, int y, int width, int height);
	// void addEnemy();
	// void addTextBox();


	void checkAllCollisions();
	void drawAllEntities();

};


#endif // ENTITY_MANAGER_H
