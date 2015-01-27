#include "Rect.h"


Rect::Rect(void) 
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	rotationDegs = 0;
}

Rect::Rect(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->rotationDegs = 0;
}

Rect::~Rect(void)
{

}

bool Rect::intersects(Rect* B)
{
	int AX1 = this->getX();
	int AX2 = AX1 + this->getWidth();
	int AY1 = this->getY();
	int AY2 = AY1 + this->getHeight();

	int BX1 = B->getX();
	int BX2 = BX1 + B->getWidth();
	int BY1 = B->getY();
	int BY2 = BY1 + B->getHeight();

	if (AX1 < BX2 &&
		BX1 < AX2 &&
		AY1 < BY2 &&
		BY1 < AY2)
	{
		return true;
	} 
	else return false;

}
