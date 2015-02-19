#include "PhysicsSystem.h"
#include "Components.h"

PhysicsSystem::PhysicsSystem(void)
{
	gravity = -0.2;
}


PhysicsSystem::~PhysicsSystem(void)
{
}

void PhysicsSystem::update(EntityManager* em)
{
	//get all the physics components
	Container<PhysicsComponent>* physicsComps = em->getComponentVector<PhysicsComponent>();

	//get all the position components
	Container<PositionComponent>* positionComps = em->getComponentVector<PositionComponent>();

	//get entities with both physics and collision
	Container<Object> ents = em->getEntities();
	for(int i=0; i<CONTAINER_SIZE; ++i)
	{
		unsigned int physicsIndex = ents.get(i).components[PHYSICS_ID];
		unsigned int positionIndex = ents.get(i).components[POSITION_ID];
		
		//for each entity that has physics and position
		if(ents.get(i).inUse[PHYSICS_ID] && ents.get(i).inUse[POSITION_ID])
		{
			PhysicsComponent& phys = physicsComps->get(physicsIndex);
			PositionComponent& pos = positionComps->get(positionIndex);

			if(phys.useGravity)
			{
				phys.ddy = phys.gravity;
			}

			phys.dx += phys.ddx;
			
			if(phys.dy < phys.maxSpeed && phys.dy > -1*phys.maxSpeed) 
			{
				phys.dy += phys.ddy;
			}

			phys.dy = phys.dy * phys.friction;
			//if(phys.dy <0.1 && phys.dy >-0.1) phys.dy = 0;
			phys.dx = phys.dx * phys.friction;
			if(phys.dx <0.1 && phys.dx >-0.1) 
			{
				phys.dx = 0;
			}

			pos.x += phys.dx;
			pos.y += phys.dy;
		}
	}
}
