#include "HUD.h"
#include "Game.h"

HUD::HUD()
{
	setEntityType(ENTITY_TYPE::HUD);
	setWidth(SCREEN_WIDTH);
	setHeight(SCREEN_HEIGHT);
	setX(-1*SCREEN_WIDTH/10);
	setY(SCREEN_HEIGHT/10);
	
	heartHealthAmt_ = 10;
	heartSize_ = 32;
	heartStartX_ = 30;
	heartStartY_ = 50;
}

HUD::~HUD()
{

}

void HUD::updateInput()
{
	int playerMaxHealth = GAME->getPlayer()->getMaxHealth();
	while(playerMaxHealth/heartHealthAmt_ > hearts.size())
	{
		Heart h = Heart();
		h.sprite = new HeartSprite(heartSize_, heartSize_, GAME->getSpriteSheet("res/HUD.tga"));
		h.x = hearts.size() * heartSize_ + heartStartX_;
		h.y = hearts.size()/10 *heartSize_ + heartStartY_;
		hearts.push_back(h);
	}

	int playerHealth = GAME->getPlayer()->getHealth();
	for(int i=0; i<hearts.size(); ++i)
	{
		//full hearts
		if(i+1 <= playerHealth/heartHealthAmt_)
		{
			hearts[i].sprite->setAnimState(ANIM_STATE::DEFAULT);
		}

		//half heart
		else if(i <= playerHealth/heartHealthAmt_ && playerHealth % heartHealthAmt_ >= heartHealthAmt_/2)
		{
			hearts[i].sprite->setAnimState(ANIM_STATE::IDLE1);
		}

		//empty heart
		else
		{
			hearts[i].sprite->setAnimState(ANIM_STATE::IDLE2);
		}
	}

}

void HUD::draw()
{
	glBindTexture(GL_TEXTURE_2D, hearts[0].sprite->getSpriteSheet()->getGLuintTexture());

	//glTranslatef(getXNorm(), getYNorm(), getZ());
	//glTranslatef(getXNorm(), getYNorm(), 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
		
	//hearts
	for(int i=0; i<hearts.size(); ++i)
	{
		glPushMatrix();
		//glTranslatef((getX()+hearts[i].x ) /SCREEN_WIDTH, (getY()+hearts[i].y/SCREEN_HEIGHT), 0);
		glTranslatef(-1 + (1.0f*hearts[i].x/SCREEN_WIDTH), 1 - (1.0f*hearts[i].y/SCREEN_HEIGHT), 0);
		hearts[i].sprite->calcNextFrame();
		glVertexPointer(3, GL_FLOAT, 0, hearts[i].sprite->getVertexPoints());
		glTexCoordPointer(2, GL_FLOAT, 0, hearts[i].sprite->getTexturePoints());
		glDrawArrays(GL_QUADS, 0, 4);
		glPopMatrix();
	}
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//glPopMatrix();
}

void HUD::debugDraw()
{

}

HeartSprite::HeartSprite(int width, int height, SpriteSheet* ss) : Sprite(width, height, ss)
{
	totalFrames_ = 0;
	numAnimations_ = 0;
	sheetWidth_ = 128;
	sheetHeight_ = 128;
	frameWidth_ = 16;
	frameHeight_ = 16;

	spriteInfo_ = NULL;

	addAnimInfo(ANIM_STATE::DEFAULT, 1);
	addAnimInfo(ANIM_STATE::IDLE1, 1);
	addAnimInfo(ANIM_STATE::IDLE2, 1);

	setAnimState(ANIM_STATE::DEFAULT);
}

HeartSprite::~HeartSprite()
{

}