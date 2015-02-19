#include "Camera.h"

Camera::Camera(void)
{
	x_ = SCREEN_WIDTH / 2;
	y_ = SCREEN_HEIGHT / 2;
	width_ = SCREEN_WIDTH;
	height_ = SCREEN_HEIGHT;
	bufX_ = 160;
	bufY_ = 200;
	reference = NULL;
}

Camera::~Camera(void)
{

}

void Camera::update()
{
	if(reference == NULL)
		return;

	setX(reference->x);
	setY(reference->y);
}

void Camera::setReference(PositionComponent* ref)
{
	if(ref == NULL) return;
	reference = ref;
}


float Camera::getXNorm(){ return 1.0f*x_/SCREEN_WIDTH; }
float Camera::getYNorm(){ return 1.0f*y_/SCREEN_HEIGHT; }
float Camera::getX(){	return x_; }
float Camera::getY(){	return y_; }

void Camera::setX(int playerX)
{
	if(playerX > x_ + bufX_) //&& playerX + bufX_ < worldWidth
	{
		x_ = playerX - bufX_; //+ playerDX
	}
	else if(playerX < x_ - bufX_) //&& playerX - bufX_ > 0
	{
		x_ = playerX + bufX_; // + playerDX
	}
}

void Camera::setY(int playerY)
{
	if(playerY > y_ + bufY_) //&& playerY + bufY_ < worldHeight
	{
		y_ = playerY - bufY_; // + playerDY
	}
	else if(playerY < y_ - bufY_) //&& playerY - bufY_ > 0
	{
		y_ = playerY + bufY_; // + playerDY
	}
}

bool Camera::isInBounds(int x, int y, int buffer)
{
	if(x_-1.15*SCREEN_WIDTH-55 > x+buffer)
		return false;
	if(x_+0.9*SCREEN_WIDTH<x-buffer)
		return false;
	if(y_-1.3*SCREEN_HEIGHT > y+buffer)
		return false;
	if(y_ + SCREEN_HEIGHT < y-buffer)
		return false;

	return true;
}