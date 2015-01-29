#include "Collision.h"

void Collision::checkCollision(Entity* A, Entity* B)
{
	if(A->getCollideBoxes().size() == 0 || B->getCollideBoxes().size() ==0)
		return;

	for (int i= 0; i<A->getCollideBoxes().size(); ++i)
	{
		for (int j=0; j<B->getCollideBoxes().size(); ++j)
		{
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

	//int x1 = A->getX();
	//int y1 = A->getY();
	//int w1 = A->getWidth();
	//int h1 = A->getHeight();

	//int x2 = B->getX();
	//int y2 = B->getY();
	//int w2 = B->getWidth();
	//int h2 = B->getHeight();

	//if(x1 > x2 && x1-x2 > w2) //left
	//	return;
	//else if(x2 > x1 && x2-x1 > w1)
	//	return;

	//if(y1 > y2 && y1-y2 > h2)
	//	return;
	//else if(y2 > y1 && y2-y1 > h1)
	//	return;

	//else 
	//{
	//	A->handleCollision(B);
	//	B->handleCollision(A);
	//	//printf("colliding!!\n");
	//}
}

