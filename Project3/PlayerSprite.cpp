
#include "PlayerSprite.h"

PlayerSprite::PlayerSprite(int width, int height, SpriteSheet* ss) : Sprite(width, height, ss)
{
	totalFrames_ = 0;
	numAnimations_ = 0;
	sheetWidth_ = 256;
	sheetHeight_ = 256;
	frameWidth_ = 64;
	frameHeight_ = 128;

	spriteInfo_ = NULL;
	
	addAnimInfo(ANIM_STATE::DEFAULT, 4);
	addAnimInfo(ANIM_STATE::DEATH, 3);
	addAnimInfo(ANIM_STATE::CROUCH, 1);

	setAnimState(ANIM_STATE::DEFAULT);
}