#ifndef SPAWNER_H
#define SPAWNER_H

#include "Terrain.h"
#include "Enemy.h"
#include <string>

//#include "EntityData.h"

class Spawner
{
private:



public:
	Spawner();
	~Spawner();

	Enemy* createEnemy(std::string id, int x, int y);
	Entity* createNPC(std::string id, int x, int y);
	Terrain* createTerrain(std::string id, int x, int y, int width, int height);
	// Item* createItem(String id, int x, int y)
	Entity* createProp(std::string id, int x, int y);
	// ParticleEmitter* createParticleEmitter(String id, int x, int y)
	// Bullet* createBullet(String id, int x, int y, float dx, float dy)

};


#endif // SPAWNER_H

