#ifndef DEBUG_DRAW_SYSTEM_H
#define DEBUG_DRAW_SYSTEM_H

#include "System.h"

class DebugDrawSystem :	public System
{
public:
	DebugDrawSystem(void);
	~DebugDrawSystem(void);

	void update(EntityManager* em);
};

#endif