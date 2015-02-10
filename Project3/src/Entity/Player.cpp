
#include "Player.h"
//#include "PlayerSprite.h"
#include "Game.h"
#include <math.h>

Player::Player(void)
{
	width_ = 140;
	height_ = 140;
	sprite_ = NULL;//new PlayerSprite(width_, height_, GAME->getSpriteSheet("res/tex_2.tga"));
	health_ = 25;
	maxHealth_ = 50;

	gravity = 1.0;
	goingUp = false;
	floating = false;
	force = 0;
	type_ = ENTITY_TYPE::PLAYER;
	setAnimState(ANIM_STATE::DEFAULT);
	initCollisionBoxes();
	setZ(-0.5);
	weapon = NULL;	
	
	permissions_.canAttack = false;
	permissions_.canCrouch = false;
	permissions_.canInteract = false;
	permissions_.canJump = false;
	permissions_.canMove = false;
	permissions_.canSwitchDirection = false;
	permissions_.canTakeDamage = false;
	permissions_.canUseMagic = false;

	state_.isAttacking = false;
	state_.isCastingSpell = false;
	state_.isCrouching = false;
	state_.isInAir = false;
	state_.isMoving = false;
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
	ANIM_STATE tempState = ANIM_STATE::DEFAULT;

	permissions_.canAttack = true;
	permissions_.canCrouch = true;
	permissions_.canInteract = true;
	permissions_.canJump = true;
	permissions_.canMove = true;
	permissions_.canSwitchDirection = true;
	permissions_.canTakeDamage = true;
	permissions_.canUseMagic = true;

	if(collidingBottom && !(collidingRight || collidingLeft))
	{
		state_.isInAir = false;
		gravity = 2;
		setDDY(0);
		setDY(0);
	}	
	if(getDY()>0)
	{
		state_.isInAir = true;
	}
	if((int)getDX() != 0)
	{
		state_.isMoving = true;
	}
	else
	{
		state_.isMoving = false;
	}

	if(state_.isCrouching && !state_.isAttacking)
	{			
		if(state_.isInAir)
		{
			if(getDY() > 0)
			{
				//tempState = ANIM_STATE::CROUCH_AIR_MOVE_UP;
			}
			else
			{
				//tempState = ANIM_STATE::CROUCH_AIR_MOVE_DOWN;
			}
		}
		else
		{
			if(state_.isMoving)
			{
				tempState = ANIM_STATE::CROUCH_MOVE;
			}
			else
			{
				tempState = ANIM_STATE::CROUCH;
			}
		}
	}
	else if(!state_.isAttacking)
	{
		if(state_.isInAir)
		{
			if(getDY() > 0)
			{
				//tempState = ANIM_STATE::AIR_MOVE_UP;
			}
			else
			{
				//tempState = ANIM_STATE::AIR_MOVE_DOWN;
			}
		}
		else
		{
			if(state_.isMoving)
				tempState = ANIM_STATE::STAND_MOVE;
			else
				tempState = ANIM_STATE::DEFAULT;
		}
	}

	//if(state_.isAttacking)
	//{
	//	if(goingUp) 
	//	{
	//		force = 0;
	//		gravity = 2;
	//		goingUp = false;
	//	}
	//}
	
	switch(animState)
	{
	case ANIM_STATE::DEFAULT:
		break;
	case ANIM_STATE::IDLE1:
		break;
	case ANIM_STATE::STAND_MOVE:
		break;
	case ANIM_STATE::AIR_MOVE_UP:				//jumping
		permissions_.canCrouch = false;
		break;
	case ANIM_STATE::AIR_MOVE_DOWN:				//falling
		break;
	case ANIM_STATE::CROUCH_AIR_MOVE_UP:		//jumping while crouched
		permissions_.canCrouch = false;
		break;
	case ANIM_STATE::CROUCH_AIR_MOVE_DOWN:		//falling while crouched
		break;
	case ANIM_STATE::CROUCH:
		break;
	case ANIM_STATE::CROUCH_MOVE:
		break;
	case ANIM_STATE::GROUND_ATTACK:
	case ANIM_STATE::GROUND_CROUCH_ATTACK:
	case ANIM_STATE::AIR_ATTACK:
	case ANIM_STATE::AIR_ATTACK_DOWN:
		permissions_.canCrouch = false;
		permissions_.canSwitchDirection = false;
		//permissions_.canJump = false;
		permissions_.canUseMagic = false;
		permissions_.canInteract = false;
		break;
	case ANIM_STATE::GROUND_MAGIC:
	case ANIM_STATE::AIR_MAGIC:
	case ANIM_STATE::CROUCH_MAGIC:
		permissions_.canCrouch = false;
		permissions_.canSwitchDirection = false;
		//permissions_.canJump = false;
		permissions_.canAttack = false;
		permissions_.canInteract = false;
		break;
	case ANIM_STATE::PUSH:
		break;
	case ANIM_STATE::SPAWN:
		permissions_.canMove = false;
		break;
	case ANIM_STATE::DEATH:
		permissions_.canMove = false;
		break;
	case ANIM_STATE::DAMAGED:
		break;
	case ANIM_STATE::CLIMB:
		break;
	case ANIM_STATE::VICTORY:
		permissions_.canMove = false;
		break;
	}

	if(permissions_.canCrouch)
	{
		if(glfwGetKey(GLFW_KEY_DOWN))
		{
			crouch();
			tempState = ANIM_STATE::CROUCH;
		}
		else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_RELEASE && state_.isCrouching)
		{
			uncrouch();
			tempState = ANIM_STATE::DEFAULT;
		}	
	}

	if(permissions_.canMove)
	{
		if(glfwGetKey(GLFW_KEY_RIGHT) || glfwGetKey(GLFW_KEY_LEFT)) 
		{
			if(permissions_.canSwitchDirection)
			{
				if(glfwGetKey(GLFW_KEY_RIGHT))
					setDirection(DIRECTION::RIGHT);
				else if (glfwGetKey(GLFW_KEY_LEFT))
					setDirection(DIRECTION::LEFT);
			}
		
			if(state_.isCrouching)
			{			
				setDDX(1.0f * ((int)glfwGetKey(GLFW_KEY_RIGHT)*1 + (int)glfwGetKey(GLFW_KEY_LEFT)*-1) );
			}
			else
			{
				setDDX(3.0f* ((int)glfwGetKey(GLFW_KEY_RIGHT)*1 + (int)glfwGetKey(GLFW_KEY_LEFT)*-1));
			}
		}
		else
			setDDX(0.0f);
	}

	if(permissions_.canJump)
	{
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
			}
		}	
	}

	

	if(permissions_.canAttack && (weapon !=NULL && !weapon->isInUse()))
	{
		attack_state = ATTACK_STATE::NONE;
		state_.isAttacking = false;
		if(glfwGetKey('X'))
		{
			if(state_.isInAir)
			{
				if(glfwGetKey(GLFW_KEY_DOWN))
				{
					setAnimState(ANIM_STATE::AIR_ATTACK_DOWN);
					attack_state = ATTACK_STATE::ATTACK_MID;
				}
				else
				{
					setAnimState(ANIM_STATE::AIR_ATTACK);
					attack_state = ATTACK_STATE::ATTACK_MID;
				}
			}
			else
			{
				if(state_.isCrouching)
				{
					setAnimState(ANIM_STATE::GROUND_CROUCH_ATTACK);
					attack_state = ATTACK_STATE::ATTACK_LOW;
				}
				else
				{
					setAnimState(ANIM_STATE::GROUND_ATTACK);
					attack_state = ATTACK_STATE::ATTACK_MID;
				}
			}
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
			state_.isAttacking = true;
			break;
		case ATTACK_STATE::ATTACK_LOW:
			weapon->attackLow();
			state_.isAttacking = true;
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

	if(!state_.isAttacking) setAnimState(tempState);
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
	state_.isCrouching = true;
	collideBoxes[1]->setActive(false);
}

void Player::uncrouch()
{	
	state_.isCrouching = false;
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

void Player::initCollisionBoxes()
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
	frameWidth_ = 64;
	frameHeight_ = 64;

	spriteInfo_ = NULL;
	
	addAnimInfo(ANIM_STATE::DEFAULT, 8);
	addAnimInfo(ANIM_STATE::STAND_MOVE, 8);
	addAnimInfo(ANIM_STATE::CROUCH, 1);

	setAnimState(ANIM_STATE::STAND_MOVE);
}

PlayerSprite::~PlayerSprite()
{

}