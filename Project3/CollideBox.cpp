#include "CollideBox.h"

CollideBox::CollideBox(int x, int y, int width, int height) : Rect(x, y, width, height)
{
	active = true;
}

CollideBox::~CollideBox()
{

}

bool CollideBox::isActive()
{
	return active;
}

void CollideBox::setActive(bool state)
{
	active = state;
}