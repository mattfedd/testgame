#include "Enemy.h"

Enemy::Enemy()
{
	width_ = 140;
	height_ = 140;
	sprite_ = NULL;//new PlayerSprite(width_, height_, GAME->getSpriteSheet("res/tex_2.tga"));

	/*gravity = 1.0;
	goingUp = false;
	floating = false;
	force = 0;*/
	type_ = ENTITY_TYPE::ENEMY;
	initCollideBoxes();
	setZ(-0.5);
	weapon = NULL;
}

Enemy::~Enemy()
{

}

void Enemy::updateInput()
{
	setDDY(-2);
	setDY(getDY() + getDDY());
	setY(getY() + getDY());
}

void Enemy::handleCollision(Entity* ent, CollideBox* us, CollideBox* e)
{
	int x1 = us->getX();
	int y1 = us->getY();
	int w1 = us->getWidth();
	int h1 = us->getHeight();

	int x2 = e->getX();
	int y2 = e->getY();
	int w2 = e->getWidth();
	int h2 = e->getHeight();

	if(ent->getEntityType() == ENTITY_TYPE::TERRAIN) 
	{
		float depthX = 100000;
		float depthY = 100000;

		if(x1 < x2 && getDX() > 0) //left
		{
			depthX = x2 - x1 - w1-2;
			collidingRight = true;
		}
		if(x1 + w1 > x2 + w2 && getDX() < 0) //right
		{
			depthX = x2 + w2 - x1+1;
			collidingLeft = true;
		}

		if(y1 < y2 && getDY() >0) //under
		{
			depthY = -1*(y2 - y1 - h1 -1);
			collidingTop = true;
		}
		if(y1 +h1 > y2 + h2 && getDY() < 0) //over
		{
			depthY = y1 - y2 - h2+1;
			collidingBottom = true;
		}
		
    	if(abs(depthX) < abs(depthY))
		{
			setX(getX() + depthX);
			setDX(0);
		}
		else
		{
			setY(getY() - depthY);
			setDY(0);
		}
	}
}

void Enemy::initCollideBoxes()
{
	collideBoxes.push_back(new CollideBox(getX()+getWidth()/2-30, getY(), 60, getHeight()));
}

EnemyBasicSprite::EnemyBasicSprite(int width, int height, SpriteSheet* ss) : Sprite(width, height, ss)
{
	totalFrames_ = 0;
	numAnimations_ = 0;
	sheetWidth_ = 512;
	sheetHeight_ = 256;
	frameWidth_ = 128;
	frameHeight_ = 128;

	spriteInfo_ = NULL;

	addAnimInfo(ANIM_STATE::DEFAULT, 1);
	addAnimInfo(ANIM_STATE::STAND_MOVE, 3);
	addAnimInfo(ANIM_STATE::CROUCH, 1);

	setAnimState(ANIM_STATE::DEFAULT);
}

EnemyBasicSprite::~EnemyBasicSprite()
{

}