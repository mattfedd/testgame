#ifndef RECT_H
#define RECT_H

#include "Includes.h"

class Rect
{
private:
	int x;
	int y;
	int width;
	int height;
	int rotationDegs;

public:
	Rect(void);
	Rect(int x, int y, int width, int height);
	~Rect(void);

	void setX(int x) {this->x = x;}
	void setY(int y) {this->y = y;}
	void setPosition(int x, int y) {this->x = x; this->y = y;}

	void setWidth(int width) {this->width = width;}
	void setHeight(int height) {this->height = height;}
	void setDimensions(int width, int height) {this->width = width; this->height = height;}

	void setRotationDegs(int degs) {rotationDegs = degs;}

	int getX() {return x;}
	int getY() {return y;}
	int getWidth() {return width;}
	int getHeight() {return height;}
	int getRotationDegs() {return rotationDegs;}
	float getRotationRads() {return 3.14159/180 * rotationDegs;}

	bool intersects(Rect* B);
};


#endif
