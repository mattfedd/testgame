#include "Collision.h"

void Collision::checkCollision(Entity* A, Entity* B)
{
	/*if(A->getCollideBoxes().size() == 0 || B->getCollideBoxes().size() ==0)
		return;*/

	for(int i=0; i<A->getInvulnerableBoxes().size(); ++i)
	{
		for(int j=0; j<B->getDamageBoxes().size(); ++j)
		{
			if(A->getInvulnerableBoxes()[i]->intersects(B->getDamageBoxes()[j]))
			{
				B->getDamageBoxes()[j]->addHitEntity(A);
				//something that says "A's invuln box just got hit"
			}
		}
	}

	for(int i=0; i<B->getInvulnerableBoxes().size(); ++i)
	{
		for(int j=0; j<A->getDamageBoxes().size(); ++j)
		{
			if(B->getInvulnerableBoxes()[i]->intersects(A->getDamageBoxes()[j]))
			{
				A->getDamageBoxes()[j]->addHitEntity(B);
				//something that says "A's invuln box just got hit"
			}
		}
	}

	for (int i= 0; i<A->getCollideBoxes().size(); ++i)
	{
		for (int d=0; d<B->getDamageBoxes().size(); ++d)
		{
			if(!B->getDamageBoxes()[d]->isInHitEntities(A))
			{
				if(A->getCollideBoxes()[i]->intersects(B->getDamageBoxes()[d]))
				{
					A->applyDamage(B->getDamageBoxes()[d]->getDamageAmount());
					B->getDamageBoxes()[d]->addHitEntity(A);
				}
			}
		}

		for (int j=0; j<B->getCollideBoxes().size(); ++j)
		{
			for (int a=0; a<A->getDamageBoxes().size(); ++a)
			{
				if(!A->getDamageBoxes()[a]->isInHitEntities(B))
				{
					if(B->getCollideBoxes()[j]->intersects(A->getDamageBoxes()[a]))
					{
						B->applyDamage(A->getDamageBoxes()[a]->getDamageAmount());
						A->getDamageBoxes()[a]->addHitEntity(B);
					}
				}
			}

			if(A->getCollideBoxes()[i]->isActive() && B->getCollideBoxes()[j]->isActive())
			{
				if (A->getCollideBoxes()[i]->intersects(B->getCollideBoxes()[j]))
				{
					A->handleCollision(B, A->getCollideBoxes()[i],B->getCollideBoxes()[j]);
					B->handleCollision(A, B->getCollideBoxes()[j],A->getCollideBoxes()[i]);	
				}
			}
		}
	}
}

