#ifndef SYSTEM_H
#define SYSTEM_H

#include "EntityManager.h"

class System
{
public:
	System() {}
	~System() {}

	virtual void update(EntityManager* em) = 0;
};

#endif