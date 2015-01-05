#include "Sprite.h"

Sprite::Sprite(int width, int height, SpriteSheet* ss)
{
	numAnimations_ = 0;
	totalFrames_ = 0;
	sheetWidth_ = 256;
	sheetHeight_ = 256;
	frameWidth_ = 64;
	frameHeight_ = 64;
	width_ = width;
	height_ = height;

	addAnimInfo(ANIM_STATE::DEFAULT, 1);

	frameNum_ = 0;
	counter_ = 0;
	animState_ = ANIM_STATE::DEFAULT;

	AnimInfo* info = getAnimInfoById(ANIM_STATE::DEFAULT);

	GLfloat temp_tex[12] = 
	{
		1.0f*info->startX/sheetWidth_,				 	    1.0f*(info->startY + frameHeight_)/sheetHeight_,
		1.0f*(info->startX + frameWidth_)/sheetWidth_, 1.0f*(info->startY + frameHeight_)/sheetHeight_,
		1.0f*(info->startX + frameWidth_)/sheetWidth_, 1.0f*info->startY/sheetHeight_,
		1.0f*info->startX/sheetWidth_,					    1.0f*info->startY/sheetHeight_,
	};

	setTexturePoints(temp_tex);

	calcVertexPoints();

	sheet_ = ss;
}

Sprite::~Sprite(void)
{

}

void Sprite::setVertexPoints(GLfloat* source)
{
	for(int i=0; i<12; ++i)
	{
		vertexPoints_[i] = source[i];
	}
}

void Sprite::setTexturePoints(GLfloat* source)
{
	for(int i=0; i<12; ++i)
	{
		texturePoints_[i] = source[i];
	}
}

GLfloat* Sprite::getVertexPoints()
{
	return vertexPoints_;
}

GLfloat* Sprite::getTexturePoints()
{
	return texturePoints_;
}

void Sprite::setAnimState(ANIM_STATE state)
{
	if(animState_ == state)
		return;
	animState_ = state;
	counter_ = 0;
	frameNum_ = 0;
}

void Sprite::setSpriteSheet(SpriteSheet* tex)
{
	sheet_ = tex;
}

SpriteSheet* Sprite::getSpriteSheet()
{
	return sheet_;
}

AnimInfo* Sprite::getAnimInfoById(ANIM_STATE state)
{
	if(spriteInfo_ == NULL)
		return NULL;

	AnimInfo* a = spriteInfo_;

	while(a->next != NULL)
	{
		if(a->id == state)
			return a;
		else
			a = a->next;
	}

	if(a->id != state)
	{
		return NULL;
	}
	else return a;
}

void Sprite::calcNextFrame()
{
	AnimInfo* info = getAnimInfoById(animState_);

	if(info == NULL)
		return;

	if(counter_ == 0)
	{
		if (frameNum_ >= info->length) frameNum_ = 0;

		int fwidth = frameWidth_;
		int fheight = frameHeight_;
		int twidth = sheetWidth_;
		int theight = sheetHeight_;

		int offsetX = info->startX;
		int offsetY = info->startY;

		int framesWidth = (sheetWidth_ / fwidth);
		int framesSoFar = offsetY/fheight * framesWidth + offsetX/fwidth + frameNum_;

		int x = framesSoFar % framesWidth * fwidth;
		int y = framesSoFar / framesWidth * fheight;

		GLfloat temp_tex[12] = 
		{
			1.0f*x/twidth,			  1.0f*y/theight,
			1.0f*(x + fwidth)/twidth, 1.0f*y/theight,
			1.0f*(x + fwidth)/twidth, 1.0f*(y+ fheight)/theight,
			1.0f*x/twidth,			  1.0f*(y+ fheight)/theight,
		};

		setTexturePoints(temp_tex);
		frameNum_++;
	}
	
	counter_ = (counter_ + 1 ) % (int)ANIM_LIMITER;
}

void Sprite::addAnimInfo(ANIM_STATE state, int length)
{
	numAnimations_++;

	AnimInfo* a = new AnimInfo;
	a->id = state;
	a->length = length;
	a->startX = (totalFrames_ % (sheetWidth_ / frameWidth_)) * frameWidth_;
	a->startY = (totalFrames_ / (sheetWidth_ / frameWidth_)) * frameHeight_;
	a->next = NULL;

	AnimInfo* temp = spriteInfo_;
	if(spriteInfo_ == NULL)
		spriteInfo_ = a;
	else
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = a;
	}
	
	totalFrames_ += length;
}

void Sprite::setWidth(int w)
{
	width_ = w;
	calcVertexPoints();
}

void Sprite::setHeight(int h)
{
	height_ = h;
	calcVertexPoints();
}

void Sprite::calcVertexPoints()
{
	GLfloat temp_vert[12] = 
	{
		0.0f*width_/SCREEN_WIDTH,1.0f*height_/SCREEN_HEIGHT, 0.0f,
		1.0f*width_/SCREEN_WIDTH,1.0f*height_/SCREEN_HEIGHT, 0.0f,
		1.0f*width_/SCREEN_WIDTH,0.0f*height_/SCREEN_HEIGHT, 0.0f,
		0.0f*width_/SCREEN_WIDTH,0.0f*height_/SCREEN_HEIGHT, 0.0f
	};
	
	setVertexPoints(temp_vert);
}