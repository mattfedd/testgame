#ifndef INVULNERABLE_BOX
#define INVULNERABLE_BOX

#include "Rect.h"

class InvulnerableBox : public Rect
{
private:

public:
	InvulnerableBox(int x, int y, int width, int height);
	~InvulnerableBox();

};


#endif