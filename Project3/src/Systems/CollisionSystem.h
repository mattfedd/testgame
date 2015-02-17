#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "System.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();

	void update(EntityManager* em);
};

#endif