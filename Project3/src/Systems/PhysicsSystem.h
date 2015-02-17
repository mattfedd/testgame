#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "system.h"
class PhysicsSystem : public System
{
public:
	PhysicsSystem(void);
	~PhysicsSystem(void);

	void update(EntityManager* em);
	float gravity;
};

#endif