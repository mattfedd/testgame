#include "CollisionSystem.h"
#include "Components.h"
#include "Game.h"


CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::update(EntityManager* em)
{
	//get all the collision components
	Container<CollisionComponent>* collisionComps = em->getComponentVector<CollisionComponent>();

	//get all the position components
	Container<PositionComponent>* positionComps = em->getComponentVector<PositionComponent>();

	//get entities with both position and collision
	Container<Object> ents = em->getEntities();
	for(int i=0; i<CONTAINER_SIZE; ++i)
	{
		unsigned int collisionIndex = ents.get(i).components[COLLISION_ID];
		unsigned int positionIndex = ents.get(i).components[POSITION_ID];
		
		//for each entity that has collision and position
		if(ents.get(i).inUse[COLLISION_ID] && ents.get(i).inUse[POSITION_ID])
		{
			CollisionComponent& c = collisionComps->get(collisionIndex);
			PositionComponent& p = positionComps->get(positionIndex);

			int mask = c.collisionMask;
			c.isCollidingMask = 0;

			//if it's allowed to collide with the world (tiles)
			if(mask & COLLISION_WORLD)
			{
				//check if it's colliding with the world
				Vector2d upperLeft = {c.AABB.left.x1 + p.x, c.AABB.top.y1 + p.y};
				Vector2d upperRight = {c.AABB.right.x2 + p.x, c.AABB.top.y2 + p.y};
				Vector2d middleLeft = {c.AABB.left.x1 + p.x, (c.AABB.top.y1-c.AABB.bottom.y1)/2 + p.y};
				Vector2d middleRight = {c.AABB.right.x2 + p.x, (c.AABB.top.y2-c.AABB.bottom.y2)/2 + p.y};
				Vector2d lowerLeft = {c.AABB.x + p.x, c.AABB.y + p.y};
				Vector2d lowerRight = {c.AABB.right.x2 + p.x, c.AABB.bottom.y2 + p.y};

				if( GAME->tiles[GAME->getTileIndexByPosition(lowerLeft.x, lowerLeft.y)] != 0 ||
					GAME->tiles[GAME->getTileIndexByPosition(upperLeft.x, upperLeft.y)] != 0 ||
					GAME->tiles[GAME->getTileIndexByPosition(middleLeft.x, middleLeft.y)] != 0 ||
					GAME->tiles[GAME->getTileIndexByPosition(middleRight.x, middleRight.y)] != 0 ||
					GAME->tiles[GAME->getTileIndexByPosition(upperRight.x, upperRight.y)] != 0 ||
					GAME->tiles[GAME->getTileIndexByPosition(lowerRight.x, lowerRight.y)] != 0 )
				{
					c.isCollidingMask |= COLLISION_WORLD;

					if(ents.get(i).inUse[PHYSICS_ID])
					{
						PhysicsComponent& phys = em->getComponentVector<PhysicsComponent>()->get(ents.get(i).components[PHYSICS_ID]);
						phys.ddy = 0;
						phys.dy = 0;
					}
				}
			}

			//check if it's colliding with other entities


			if(mask & COLLISION_PLAYER)
			{
				//check if it's colliding with the player

			}

			if(mask & COLLISION_ENEMY)
			{
				//check if it's colliding with an enemy
			}

			if(mask & COLLISION_INTERACTABLE)
			{
				//check if it's colliding with an interactable

			}

			if(mask & COLLISION_ITEM)
			{
				//check if it's colliding with an item drop

			}

			if(mask & COLLISION_PLAYERBULLET)
			{
				//check if it's colliding with a player's bullet

			}
			
			if(mask & COLLISION_ENEMYBULLET)
			{
				//check if it's colliding with an enemy's bullet

			}
		}
	}
}