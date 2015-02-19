#ifndef RECT_H
#define RECT_H

#include "Includes.h"

class Rect
{

public:
	int x;
	int y;
	int width;
	int height;
	Rect(void);
	Rect(int x, int y, int width, int height);
	~Rect(void);

	void setX(int x) {this->x = x;}
	void setY(int y) {this->y = y;}
	void setPosition(int x, int y) {this->x = x; this->y = y;}

	void setWidth(int width) {this->width = width;}
	void setHeight(int height) {this->height = height;}
	void setDimensions(int width, int height) {this->width = width; this->height = height;}

	int getX() {return x;}
	int getY() {return y;}
	int getWidth() {return width;}
	int getHeight() {return height;}

	bool intersects(Rect* B);
};


#endif
