
#include "Player.h"
#include "PlayerSprite.h"

Player::Player(void)
{
	sprite_ = new PlayerSprite(100, 100, new SpriteSheet("tex_2.tga"));
}

Player::~Player(void)
{

}

void Player::updateInput()
{
	//move up or down
	if(GAME->getInput()->getStatus()->upArrow) 
		setDDY(2.0f);
	if(GAME->getInput()->getStatus()->downArrow) 
		setDDY(-2.0f);
	if(!GAME->getInput()->getStatus()->upArrow && !GAME->getInput()->getStatus()->downArrow) 
		setDDY(0.0f);

	//move left or right
	if(GAME->getInput()->getStatus()->rightArrow) 
		setDDX(2.0f);
	if(GAME->getInput()->getStatus()->leftArrow) 
		setDDX(-2.0f);
	if(!GAME->getInput()->getStatus()->leftArrow && !GAME->getInput()->getStatus()->rightArrow) 
		setDDX(0.0f);

	float friction = 0.0f;
	float value = 0.0f;

	friction = getDX() * -0.1;
	value = getDX() + getDDX() + friction;
	if(value < 0.5 && value > -0.5) 
	{
		value = 0.0f;
	}
	setDX(value);
	
	friction = getDY() * -0.1;
	value = getDY() + getDDY() + friction;
	if(value < 0.5 && value > -0.5) 
	{
		value = 0.0f;
	}
	setDY(value);

	setX(getX() + getDX());
	setY(getY() + getDY());
}