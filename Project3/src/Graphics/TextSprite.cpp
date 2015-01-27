#include "TextSprite.h"

TextSprite::TextSprite(int width, int height, SpriteSheet* ss) : Sprite(width, height, ss)
{
	index = 1; // default to ! so that we know it works.

	sheetWidth_ = 640;
	sheetHeight_ = 108;
	frameWidth_ = 20;
	frameHeight_ = 36;
}

TextSprite::~TextSprite()
{

}

void TextSprite::setLetter(char c)
{
	index = (int) c - 32;
}

void TextSprite::calcLetter()
{
	int fwidth = frameWidth_;
	int fheight = frameHeight_;
	int twidth = sheetWidth_;
	int theight = sheetHeight_;

	int offsetX = 0;
	int offsetY = 0;

	int framesWidth = (sheetWidth_ / fwidth);
	int framesSoFar = offsetY/fheight * framesWidth + offsetX/fwidth + frameNum_;

	int x = index % framesWidth * fwidth;
	int y = index / framesWidth * fheight;

	GLfloat temp_tex[12] = 
	{
		1.0f*x/twidth,			  1.0f*y/theight,
		1.0f*(x + fwidth)/twidth, 1.0f*y/theight,
		1.0f*(x + fwidth)/twidth, 1.0f*(y+ fheight)/theight,
		1.0f*x/twidth,			  1.0f*(y+ fheight)/theight,
	};

	setTexturePoints(temp_tex);
}