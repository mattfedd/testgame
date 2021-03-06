#ifndef CAMERA_H
#define CAMERA_H

#include "Includes.h"
#include "Components.h"

class Camera
{
private:
	float x_;
	float y_;
	int width_;
	int height_;
	int bufX_;
	int bufY_;
	
	float dx_;
	float dy_;

	PositionComponent* reference;

public:
	Camera(void);
	~Camera(void);

	float getXNorm();
	float getYNorm();
	float getX();
	float getY();

	void setX(int playerX);
	void setY(int playerY);

	void update();
	void setReference(PositionComponent* pos);
	bool isInBounds(int x, int y, int buffer);
};

#endif