
#include "Player.h"
//#include "PlayerSprite.h"
#include "Game.h"
#include <math.h>

Player::Player(void)
{
	width_ = 140;
	height_ = 140;
	sprite_ = NULL;//new PlayerSprite(width_, height_, GAME->getSpriteSheet("res/tex_2.tga"));

	gravity = 1.0;
	goingUp = false;
	floating = false;
	force = 0;
	type_ = ENTITY_TYPE::PLAYER;
	initCollideBoxes();
	setZ(-0.5);
	weapon = NULL;
}

Player::~Player(void)
{

}

void Player::updateInput()
{
	
	/* TODO : set a priority for the current direction. For instance, if 
		we're currently moving left and I press right, it does/doesn't switch. 
		Same for right to left. 
	*/

	if(glfwGetKey(GLFW_KEY_RIGHT)) 
	{
		if(weapon != NULL && !weapon->isInUse())
			sprite_->setDirection(DIRECTION::RIGHT);
		
		if(sprite_->getAnimState() == ANIM_STATE::CROUCH)
		{
			setDDX(1.0f);
		}
		else
		{
			sprite_->setAnimState(ANIM_STATE::GROUND_MOVE);
			setDDX(3.0f);
		}
	}
	else if(glfwGetKey(GLFW_KEY_LEFT)) 
	{
 		if(weapon != NULL && !weapon->isInUse())
			sprite_->setDirection(DIRECTION::LEFT);
		if(sprite_->getAnimState() == ANIM_STATE::CROUCH)
		{
			setDDX(-1.0f);
		}
		else
		{
			sprite_->setAnimState(ANIM_STATE::GROUND_MOVE);
			setDDX(-3.0f);
		}
	}
	if(!glfwGetKey(GLFW_KEY_LEFT) && !glfwGetKey(GLFW_KEY_RIGHT)) 
		setDDX(0.0f);

	if(collidingBottom && !(collidingRight || collidingLeft))
	{
		gravity = 2;
		setDDY(0);
		setDY(0);
	}	


	if(weapon == NULL || (weapon != NULL && !weapon->isInUse()))
	{
		attack_state = ATTACK_STATE::NONE;
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
			if(collidingBottom && (int)getDY() == 0)
			{
				force = 8.5;
				goingUp = true;

			}
			else 
			{
   				if(force >0) force-=1.2;
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
				if(sprite_->getAnimState() != ANIM_STATE::CROUCH)
					sprite_->setAnimState(ANIM_STATE::DEFAULT);
			}
		}	

		if(glfwGetKey('X'))
		{
			attack_state = ATTACK_STATE::ATTACK_MID;
			//sprite_->setAnimState(ANIM_STATE::ATTACK);
		}

		if(glfwGetKey(GLFW_KEY_DOWN) && glfwGetKey('X'))
		{
			attack_state = ATTACK_STATE::ATTACK_LOW;
			//sprite_->setAnimState(ANIM_STATE::ATTACK_LOW);
		}
	}

	//state stuff
	if(weapon != NULL)
	{
		switch(attack_state)
		{
		case ATTACK_STATE::NONE:
			break;
		case ATTACK_STATE::ATTACK_MID:
			weapon->attackMid();
			break;
		case ATTACK_STATE::ATTACK_LOW:
			weapon->attackLow();
			break;
		case ATTACK_STATE::ATTACK_HIGH:
			weapon->attackHigh();
			break;
		default:
			break;
		}
	}

	for(int i=0; i<damageBoxes.size(); ++i)
	{
		damageBoxes[i]->update();
		if(damageBoxes[i]->isDead())
		{
			DamageBox* box = damageBoxes[i];
			damageBoxes.erase(damageBoxes.begin()+i);
			i--;
			delete box;
		}
	}

	float friction = 0.0f;
	float value = 0.0f;
	setDDY(force -gravity);

	friction = (collidingBottom && !(collidingLeft && collidingRight)) ? getDX() * -0.2 : getDX()*-0.15;	
	
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

void Player::handleCollision(Entity *ent, CollideBox* us, CollideBox* e)
{
	//for each collidebox
	//check which part is colliding
	//then set flags

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

void Player::crouch()
{
	sprite_->setAnimState(ANIM_STATE::CROUCH);
	collideBoxes[1]->setActive(false);
}

void Player::uncrouch()
{
	if(getDX() > 0 || getDX() < 0)
	{
		sprite_->setAnimState(ANIM_STATE::GROUND_MOVE);
	}
	else
		sprite_->setAnimState(ANIM_STATE::DEFAULT);
	collideBoxes[1]->setActive(true);
}

void Player::attackGroundHigh()
{

}

void Player::attackGroundMid()
{
	//sprite_->setAnimState(ANIM_STATE::ATTACK);
}

void Player::attackGroundLow()
{

}

void Player::initCollideBoxes()
{
	//bottom
	collideBoxes.push_back(new CollideBox(getX()+getWidth()/2 -25, getY(), 50, getHeight()/2));
	
	//top
	collideBoxes.push_back(new CollideBox(getX()+getWidth()/2 -25, getY()+getHeight()/2, 50, getHeight()/2));
}

Weapon* Player::getWeapon()
{
	return weapon;
}

void Player::setWeapon(Weapon* weapon)
{
	this->weapon = weapon;
	weapon->setParent(this);
}

/*-------------------------------------------------------------------------------------------------------------
----------------------------------------------SPRITE STUFF-----------------------------------------------------
--------------------------------------------------------------------------------------------------------------- */
PlayerSprite::PlayerSprite(int width, int height, SpriteSheet* ss) : Sprite(width, height, ss)
{
	totalFrames_ = 0;
	numAnimations_ = 0;
	sheetWidth_ = 512;
	sheetHeight_ = 256;
	frameWidth_ = 128;
	frameHeight_ = 128;

	spriteInfo_ = NULL;
	
	addAnimInfo(ANIM_STATE::DEFAULT, 1);
	addAnimInfo(ANIM_STATE::GROUND_MOVE, 3);
	addAnimInfo(ANIM_STATE::CROUCH, 1);

	setAnimState(ANIM_STATE::GROUND_MOVE);
}

PlayerSprite::~PlayerSprite()
{

}