
#include "Player.h"
#include "PlayerSprite.h"

Player::Player(void)
{
	width_ = 50;
	height_ = 50;
	sprite_ = new PlayerSprite(width_, height_, new SpriteSheet("tex_2.tga"));
	colliding = false;

	gravity = 1.0;
	goingUp = false;
	floating = false;
	force = 0;
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
	if(GAME->getInput()->getStatus()->rightArrow) 
		setDDX(2.0f);
	if(GAME->getInput()->getStatus()->leftArrow) 
		setDDX(-2.0f);
	if(!GAME->getInput()->getStatus()->leftArrow && !GAME->getInput()->getStatus()->rightArrow) 
		setDDX(0.0f);

	if(colliding)
	{
		gravity = 2;
		setDDY(0);
		setDY(0);
	}	

	if(glfwGetKey(GLFW_KEY_SPACE))
	{
		if(colliding) 
		{
			force = 8.5;
			goingUp = true;
			sprite_->setAnimState(ANIM_STATE::AIR_MOVE_UP_RIGHT);
		}
		else 
		{
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

	friction = colliding ? getDX() * -0.15 : getDX()*-0.1;
	
	
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

	printf("gravity :%f, ddy :%f, dy :%f\n", gravity, getDDY(), getDY());

	setX(getX() + getDX());
	setY(getY() + getDY());

	colliding = false;
}