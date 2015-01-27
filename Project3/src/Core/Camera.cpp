#include "Camera.h"


Camera::Camera(void)
{
	x_ = SCREEN_WIDTH / 2;
	y_ = SCREEN_HEIGHT / 2;
	width_ = SCREEN_WIDTH;
	height_ = SCREEN_HEIGHT;
	bufX_ = 160;
	bufY_ = 200;
	attachable_ = NULL;
}

Camera::~Camera(void)
{

}

void Camera::update()
{
	if(attachable_ == NULL) return;

	setX(attachable_->getX());
	setY(attachable_->getY());
}

bool Camera::setAttachable(Entity* entity)
{
	if(entity == NULL) return false;

	attachable_ = entity;
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
