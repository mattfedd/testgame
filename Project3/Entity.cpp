#include "Entity.h"

Entity::Entity(void)
{
	dx_ = 0;
	dy_ = 0;
	ddx_ = 0;
	ddy_ = 0;
	maxSpeed_ = 1;
}
Entity::~Entity(void)
{

}

float Entity::getXNorm(){ return 1.0f*x_/SCREEN_WIDTH; }
float Entity::getYNorm(){ return 1.0f*y_/SCREEN_HEIGHT; }
float Entity::getZNorm(){ return z_ * 1.0f; }
int Entity::getX(){ return x_; }
int Entity::getY(){ return y_; }
int Entity::getZ(){ return z_; }
float Entity::getDX(){ return dx_; }
float Entity::getDY(){ return dy_; }
float Entity::getDDX(){ return ddx_; }
float Entity::getDDY(){ return ddy_; }
int Entity::getWidth(){ return width_; }
int Entity::getHeight(){ return height_; }
int Entity::getMaxSpeed(){ return maxSpeed_; }
//long Entity::getRadiusSquared(){ return }

void Entity::setPosition(int x, int y, int z)
{
	if(x != 0) setX(x);
	if(y != 0) setY(y);
	if(z != 0) setZ(z);
}
void Entity::setX(int x){ x_ = x; }
void Entity::setY(int y){ y_ = y; }
void Entity::setZ(int z){ x_ = z; }
void Entity::setDX(float dx)
{ 
	if(dx < maxSpeed_ && dx > -1*maxSpeed_) 
		dx_ = dx;
	else if(dx > maxSpeed_)
		dx_ = maxSpeed_;
	else if(dx < -1*maxSpeed_)
		dx_= -1*maxSpeed_;
}
void Entity::setDY(float dy)
{ 
	if(dy < maxSpeed_ && dy > -1*maxSpeed_) 
		dy_ = dy;
	else if(dy > maxSpeed_)
		dy_ = maxSpeed_;
	else if(dy < -1*maxSpeed_)
		dy_ = -1*maxSpeed_;
}
void Entity::setDDX(float ddx){ddx_ = ddx; }
void Entity::setDDY(float ddy){ddy_ = ddy; }
void Entity::setSize(int width, int height){ width_ = width; height_ = height; }
void Entity::setMaxSpeed(int val){ maxSpeed_ = val; }
//void Entity::setRadiusSquared(long val){}

void Entity::updateInput()
{

}

void Entity::updateCollisions()
{

}

void Entity::updateGraphics()
{

}

void Entity::draw()
{
	if(sprite_ == NULL)
		return;

	glBindTexture(GL_TEXTURE_2D, sprite_->getTexture()->getGLuintTexture());

	glPushMatrix();
	glTranslatef(getXNorm() - GAME->getCamera()->getXNorm(), getYNorm() - GAME->getCamera()->getYNorm(), 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);	
		
	glVertexPointer(3, GL_FLOAT, 0, sprite_->getVertexPoints());
	glTexCoordPointer(2, GL_FLOAT, 0, sprite_->getTexturePoints());
	glDrawArrays(GL_QUADS, 0, 4);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();
}
