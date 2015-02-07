#include "Entity.h"
#include "Game.h"

Entity::Entity(void)
{
	x_ = 0;
	y_ = 0;
	z_ = 0;

	width_ = 50;
	height_ = 40;
	dx_ = 0;
	dy_ = 0;
	ddx_ = 0;
	ddy_ = 0;
	maxSpeed_ = 30;
	sprite_ = NULL;//new Sprite(width_, height_, GAME->getSpriteSheet("res/tex.tga"));
	collidingTop = false;
	collidingBottom = false;
	collidingLeft = false;
	collidingRight = false;
	type_ = ENTITY_TYPE::ENTITY;
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
ENTITY_TYPE Entity::getEntityType(){ return type_; }
ANIM_STATE Entity::getAnimState(){ return animState; }

void Entity::setPosition(int x, int y, int z)
{
	if(x != 0) setX(x);
	if(y != 0) setY(y);
	if(z != 0) setZ(z);
}
void Entity::setX(int x)
{ 
	int dx = x-this->getX();
	x_ = x; 

	if(collideBoxes.size() == 0)
	{
		return;
	}

	for (int i=0; i<collideBoxes.size(); ++i) 
	{
		collideBoxes[i]->setX(collideBoxes[i]->getX() + dx);
	}

	if(damageBoxes.size() == 0)
	{
		return;
	}

	for (int i=0; i<damageBoxes.size(); ++i) 
	{
		damageBoxes[i]->setX(damageBoxes[i]->getX() + dx);
	}
}

void Entity::setY(int y)
{ 
	int dy = y-this->getY();
	y_ = y; 

	if(collideBoxes.size() == 0) 
	{
		return;
	}

	for (int i=0; i<collideBoxes.size(); ++i)
	{
		collideBoxes[i]->setY(collideBoxes[i]->getY() + dy);
	}

	if(damageBoxes.size() == 0) 
	{
		return;
	}

	for (int i=0; i<damageBoxes.size(); ++i)
	{
		damageBoxes[i]->setY(damageBoxes[i]->getY() + dy);
	}
}

void Entity::setZ(int z){ z_ = z; }
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
void Entity::setWidth(int w)
{ 
	width_ = w; 
	if(sprite_ != NULL) sprite_->setWidth(w);
	
	if(collideBoxes.size() == 0) 
	{
		return;
	}

	for (int i=0; i<collideBoxes.size(); ++i)
	{
		collideBoxes[i]->setWidth(w);
	}
}
void Entity::setHeight(int h)
{ 
	height_ = h; 
	if(sprite_ != NULL) sprite_->setHeight(h);
		
	if(collideBoxes.size() == 0) 
	{
		return;
	}

	for (int i=0; i<collideBoxes.size(); ++i)
	{
		collideBoxes[i]->setHeight(h);
	}
}
void Entity::setSize(int width, int height)
{ 
	setWidth(width);
	setHeight(height);
}

void Entity::setMaxSpeed(int val){ maxSpeed_ = val; }
//void Entity::setRadiusSquared(long val){}
void Entity::setEntityType(ENTITY_TYPE type){ type_ = type; }

void Entity::initCollideBoxes()
{
	//collideBoxes = 0;
}

void Entity::handleCollision(Entity* ent, CollideBox* us, CollideBox* e)
{
	//check what we're colliding with, then react appropriately


}

void Entity::updateInput()
{
	return;
}

void Entity::updateCollisions()
{
	return;
}

void Entity::updateGraphics()
{

}

void Entity::addDamageBox(int relativeX, int relativeY, int width, int height, int lifetime, int damage)
{
	int boxX = getX() + getWidth()/2 + (sprite_->getDirection()==DIRECTION::RIGHT ? 1 : -1)*relativeX - width/2;
	int boxY = getY() + relativeY;

	DamageBox* box = new DamageBox(boxX, boxY, width, height);
	
	if(lifetime > 0)
		box->setLifeTime(lifetime);
	
	box->setDamageAmount(damage);

	damageBoxes.push_back(box);
}

void Entity::draw()
{
	if(sprite_ == NULL)
		return;

	if(!GAME->isPaused()) sprite_->calcNextFrame();
	
	glBindTexture(GL_TEXTURE_2D, sprite_->getSpriteSheet()->getGLuintTexture());

	glPushMatrix();
	glTranslatef(getXNorm() - GAME->getCamera()->getXNorm(), getYNorm() - GAME->getCamera()->getYNorm(), getZ());
	//glTranslatef(getXNorm(), getYNorm(), 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
		
	glVertexPointer(3, GL_FLOAT, 0, sprite_->getVertexPoints());
	glTexCoordPointer(2, GL_FLOAT, 0, sprite_->getTexturePoints());
	glDrawArrays(GL_QUADS, 0, 4);

	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();

	#ifdef DEBUG
	debugDraw();
	#endif
}

void Entity::debugDraw()
{
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPushMatrix();
	glTranslatef(getXNorm() - GAME->getCamera()->getXNorm(), getYNorm() - GAME->getCamera()->getYNorm(), getZ());
	
	for(int i=0; i<collideBoxes.size(); ++i)
	{
		if(collideBoxes[i]->isActive())
		{
			GLfloat tempVerts[4] = 
			{
				1.0f*(collideBoxes[i]->getX()-getX())/SCREEN_WIDTH,1.0f*(collideBoxes[i]->getY()-getY())/SCREEN_HEIGHT,
				1.0f*(collideBoxes[i]->getWidth()+collideBoxes[i]->getX()-getX())/SCREEN_WIDTH,1.0f*(collideBoxes[i]->getHeight()+collideBoxes[i]->getY()-getY())/SCREEN_HEIGHT
			};

			glLineWidth(1.5); 
			glColor3f(0.0, 1.0, 0.0);

			glBegin(GL_LINES);
			glVertex2f(tempVerts[0], tempVerts[3]);
			glVertex2f(tempVerts[2], tempVerts[3]);
			glEnd();

			glBegin(GL_LINES);
			glVertex2f(tempVerts[2], tempVerts[1]);
			glVertex2f(tempVerts[0], tempVerts[1]);
			glEnd();

			glBegin(GL_LINES);
			glVertex2f(tempVerts[2], tempVerts[3]);
			glVertex2f(tempVerts[2], tempVerts[1]);
			glEnd();

			glBegin(GL_LINES);
			glVertex2f(tempVerts[0], tempVerts[1]);
			glVertex2f(tempVerts[0], tempVerts[3]);
			glEnd();

			glColor3f(1.0,1.0,1.0);
		}
	}

	for(int i=0; i<damageBoxes.size(); ++i)
	{
		GLfloat tempVerts[4] = 
		{
			1.0f*(damageBoxes[i]->getX()-getX())/SCREEN_WIDTH,1.0f*(damageBoxes[i]->getY()-getY())/SCREEN_HEIGHT,
			1.0f*(damageBoxes[i]->getWidth()+damageBoxes[i]->getX()-getX())/SCREEN_WIDTH,1.0f*(damageBoxes[i]->getHeight()+damageBoxes[i]->getY()-getY())/SCREEN_HEIGHT
		};

		glLineWidth(2.5); 
		glColor3f(1.0, 0.0, 0.0);
		
		glBegin(GL_LINES);
		glVertex2f(tempVerts[0], tempVerts[3]);
		glVertex2f(tempVerts[2], tempVerts[3]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(tempVerts[2], tempVerts[1]);
		glVertex2f(tempVerts[0], tempVerts[1]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(tempVerts[2], tempVerts[3]);
		glVertex2f(tempVerts[2], tempVerts[1]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(tempVerts[0], tempVerts[1]);
		glVertex2f(tempVerts[0], tempVerts[3]);
		glEnd();

		glColor3f(1.0,1.0,1.0);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();
}