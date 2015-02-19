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

	int sx = GAME->getTileData().startX;
	int sy = GAME->getTileData().startY;
	int tileWidth = GAME->getTileData().tileWidth;
	int tileHeight = GAME->getTileData().tileHeight;
	int tileArrayWidth = GAME->getTileData().arrayWidth;

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
			
			float dx = 0;
			float dy = 0;
			int x = 0;
			int y = 0;
			int moveX = 0;
			int moveY = 0;

			if(ents.get(i).inUse[PHYSICS_ID])
			{
				PhysicsComponent& phys = em->getComponentVector<PhysicsComponent>()->get(ents.get(i).components[PHYSICS_ID]);
				dx = phys.dx;
				dy = phys.dy;
			}

			//if it's allowed to collide with the world (tiles)
			if(mask & COLLISION_WORLD)
			{
				Vector2d upperLeft = {c.AABB.x+c.AABB.width/4+p.x, c.AABB.y+c.AABB.height+p.y};
				Vector2d upperRight = {c.AABB.x+3*c.AABB.width/4+p.x, c.AABB.y+c.AABB.height+p.y};
				Vector2d middleUpperLeft = {c.AABB.x + p.x, p.y+3*c.AABB.height/4};
				Vector2d middleUpperRight = {c.AABB.x + p.x+c.AABB.width, p.y+3*c.AABB.height/4};
				Vector2d middleLowerLeft = {c.AABB.x + p.x,p.y+c.AABB.height/4};
				Vector2d middleLowerRight = {c.AABB.x + p.x+c.AABB.width,p.y+c.AABB.height/4};
				Vector2d lowerLeft = {c.AABB.x+c.AABB.width/4+p.x, c.AABB.y+p.y};
				Vector2d lowerRight = {c.AABB.x+3*c.AABB.width/4+p.x, c.AABB.y+p.y};
				int A,B,C,D,E,F,G,H;
				int depthY = 0;
				int depthX = 0;

				if( (GAME->tiles[A=GAME->getTileIndexByPosition(upperRight.x, upperRight.y)] != 0 ||
					GAME->tiles[B=GAME->getTileIndexByPosition(upperLeft.x, upperLeft.y)] != 0) && dy >=0)
				{
					//colliding top
					c.isCollidingMask |= COLLISION_WORLD;
					depthY = GAME->getTilePositionByIndex(A).y-upperLeft.y;
				}

				if( (GAME->tiles[C=GAME->getTileIndexByPosition(middleUpperLeft.x, middleUpperLeft.y)] != 0 ||
					GAME->tiles[D=GAME->getTileIndexByPosition(middleLowerLeft.x, middleLowerLeft.y)] != 0) && dx <=0)
				{
					//colliding left
					c.isCollidingMask |= COLLISION_WORLD;
					depthX = GAME->getTilePositionByIndex(C).x+tileWidth-middleUpperLeft.x;
				}

				if( (GAME->tiles[E=GAME->getTileIndexByPosition(middleUpperRight.x, middleUpperRight.y)] != 0 ||
					GAME->tiles[F=GAME->getTileIndexByPosition(middleLowerRight.x, middleLowerRight.y)] != 0) && dx >=0)
				{
					//colliding right
					c.isCollidingMask |= COLLISION_WORLD;
					depthX = GAME->getTilePositionByIndex(E).x-middleUpperRight.x;
				}

				if( (GAME->tiles[G=GAME->getTileIndexByPosition(lowerLeft.x, lowerLeft.y)] != 0 ||
					GAME->tiles[H=GAME->getTileIndexByPosition(lowerRight.x, lowerRight.y)] != 0) && dy <=0)
				{
					//colliding bottom
					c.isCollidingMask |= COLLISION_WORLD;
					depthY = GAME->getTilePositionByIndex(G).y+tileHeight-lowerLeft.y;
				}

				p.x += depthX;
				p.y += depthY;
					
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
