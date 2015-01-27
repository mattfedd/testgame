
#include "Player.h"
#include "PlayerSprite.h"
#include <math.h>

Player::Player(void)
{
	width_ = 50;
	height_ = 100;
	sprite_ = new PlayerSprite(width_, height_, new SpriteSheet("tex_2.tga"));

	gravity = 1.0;
	goingUp = false;
	floating = false;
	force = 0;
	type_ = ENTITY_TYPE::PLAYER;
	initCollideBoxes();
}

Player::~Player(void)
{

}

void Player::updateInput()
{
	//move up or down
	/*if(GAME->getInput()->getStatus()->upArrow) 
		setDDY(2.0f);
	if(GAME->getInput()->getStatus()->downArrow) 
		setDDY(-2.0f);
	if(!GAME->getInput()->getStatus()->upArrow && !GAME->getInput()->getStatus()->downArrow) 
		setDDY(0.0f);*/

	//move left or right
	//if(!glfwGetKey(GLFW_KEY_LEFT) || !glfwGetKey(GLFW_KEY_RIGHT))

	
	/* TODO : set a priority for the current direction. For instance, if 
		we're currently moving left and I press right, it does/doesn't switch. 
		Same for right to left. 
	*/
	if(glfwGetKey(GLFW_KEY_RIGHT)) 
	{
		sprite_->setDirection(DIRECTION::RIGHT);
		setDDX(2.0f);
	}
	else if(glfwGetKey(GLFW_KEY_LEFT)) 
	{
		sprite_->setDirection(DIRECTION::LEFT);
		setDDX(-2.0f);
	}
	if(!glfwGetKey(GLFW_KEY_LEFT) && !glfwGetKey(GLFW_KEY_RIGHT)) 
		setDDX(0.0f);

	if(collidingBottom)
	{
		gravity = 2;
		setDDY(0);
		setDY(0);
	}	

	if(glfwGetKey(GLFW_KEY_DOWN)&& glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		crouch();
	}
	else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_RELEASE && glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		uncrouch();
	}

    if(glfwGetKey(GLFW_KEY_SPACE))
	{
		if(collidingBottom) 
		{
			force = 8.5;
			goingUp = true;
			if(sprite_->getAnimState() == ANIM_STATE::CROUCH)
			{
				sprite_->setAnimState(ANIM_STATE::DEATH);
			}
		}
		else 
		{
			if(collidingLeft || collidingRight)
			{
 				int q = 0;
			}

   			if(force >0) force--;
			if(force < 0) 
			{
				force = 0;
			}
		}
	}
	else
	{
		if(goingUp) 
		{
			force = 0;
			gravity = 2;
			goingUp = false;
			sprite_->setAnimState(ANIM_STATE::DEFAULT);
		}
	}	

	float friction = 0.0f;
	float value = 0.0f;
	setDDY(force -gravity);

	friction = (collidingBottom && !(collidingLeft || collidingRight)) ? getDX() * -0.15 : getDX()*-0.1;	
	
	value = getDX() + getDDX() + friction;
	if(value < 0.5 && value > -0.5) 
	{
		value = 0.0f;
	}
	setDX(value);
	
	friction = getDY() * 0;
	value = getDY() + getDDY() + friction;
	if(value < 0.01 && value > -0.01) 
	{
		value = 0.0f;
	}
	setDY(value);

	//printf("gravity :%f, ddy :%f, dy :%f\n", gravity, getDDY(), getDY());

	setX(getX() + getDX());
	setY(getY() + getDY());

	collidingTop = false;
	collidingBottom = false;
	collidingLeft = false;
	collidingRight = false;
}

void Player::handleCollision(Entity* e)
{
	int x1 = getX();
	int y1 = getY();
	int w1 = getWidth();
	int h1 = getHeight();

	int x2 = e->getX();
	int y2 = e->getY();
	int w2 = e->getWidth();
	int h2 = e->getHeight();

	if(e->getEntityType() == ENTITY_TYPE::ENTITY) 
	{
		float depthX = 100000;
		float depthY = 100000;

		if(x1 < x2) //left
		{
			depthX = x2 - x1 - w1-2;
			collidingRight = true;
		}
		if(x1 + w1 > x2 + w2) //right
		{
			depthX = x2 + w2 - x1+1;
			collidingLeft = true;
		}

		if(y1 < y2) //under
		{
			depthY = -1*(y2 - y1 - h1 -1);
			collidingTop = true;
		}
		if(y1 +h1 > y2 + h2) //over
		{
			depthY = y1 - y2 - h2+1;
			collidingBottom = true;
		}

		if(depthX == 0 || depthY == 0)
		{
			setDX(0);
			setDY(0);
			return;
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

void Player::crouch()
{
	sprite_->setAnimState(ANIM_STATE::CROUCH);
	collideBoxes[1]->setActive(false);
}

void Player::uncrouch()
{
	sprite_->setAnimState(ANIM_STATE::DEFAULT);
	collideBoxes[1]->setActive(true);
}

void Player::attackGroundHigh()
{

}

void Player::attackGroundMid()
{

}

void Player::attackGroundLow()
{

}

void Player::initCollideBoxes()
{
	//bottom
	collideBoxes.push_back(new CollideBox(getX(), getY(), getWidth(), getHeight()/2));
	
	//top
	collideBoxes.push_back(new CollideBox(getX(), getY()+getHeight()/2, getWidth(), getHeight()/2));
}