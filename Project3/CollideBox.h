#ifndef COLLIDE_BOX_H
#define COLLIDE_BOX_H

#include "Rect.h"

class CollideBox : public Rect
{
private:
	bool active;

public:
	CollideBox(int x, int y, int width, int height);
	~CollideBox(void);

	bool isActive();
	void setActive(bool state);
};

#endif