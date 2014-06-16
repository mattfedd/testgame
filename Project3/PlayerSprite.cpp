
#include "PlayerSprite.h"

PlayerSprite::PlayerSprite(int width, int height, SpriteSheet* ss) : Sprite(width, height, ss)
{
	totalFrames_ = 0;
	numAnimations_ = 0;
	sheetWidth_ = 256;
	sheetHeight_ = 256;

	spriteInfo_ = NULL;
	addAnimInfo(ANIM_STATE::DEATH, 5);
	addAnimInfo(ANIM_STATE::DEFAULT, 6);

	setAnimState(ANIM_STATE::DEFAULT);
}