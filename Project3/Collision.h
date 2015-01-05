#ifndef COLLISION_H
#define COLLISION_H

#include "Entity.h"

namespace Collision {

	void checkCollision(Entity* A, Entity* B);
	//bool isIntersecting(Point2d A1, Point2d A2, Point2d B1, Point2d B2);
}

#endif