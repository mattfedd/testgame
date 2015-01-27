#ifndef SPRITE_H
#define SPRITE_H

#include "Includes.h"
#include "SpriteSheet.h"

//#include "Game.h"
struct AnimInfo
{
	ANIM_STATE id;
	int length;
	int startX;
	int startY;
	AnimInfo* next;
};

class Sprite
{
private:
	GLfloat vertexPoints_[12];
	GLfloat texturePoints_[12];
	
	SpriteSheet* sheet_;

protected:
	void setVertexPoints(GLfloat* source);
	void setTexturePoints(GLfloat* source);

	int numAnimations_;
	int width_;
	int height_;
	int sheetWidth_;
	int sheetHeight_;
	int counter_;
	int frameNum_;
	int totalFrames_;
	int frameWidth_;
	int frameHeight_;
	DIRECTION dir_;

	ANIM_STATE animState_;
	AnimInfo* spriteInfo_;

public:
	//we need width and height for the general vertex points
	//spritesheet for the texture reference
	Sprite(int width, int height, SpriteSheet* ss);
	~Sprite(void);
	
	void setSpriteSheet(SpriteSheet* tex);
	SpriteSheet* getSpriteSheet();
	GLfloat* getVertexPoints();
	GLfloat* getTexturePoints();

	//TODO : add getTexture() which just calls the SpriteSheet getGLuintTexture(), so we don't have to expose the spritesheet publicly

	void setWidth(int w);
	void setHeight(int h);
	void setDirection(DIRECTION direction);
	DIRECTION getDirection() {return dir_;}

	void setAnimState(ANIM_STATE new_state);
	ANIM_STATE getAnimState() {return animState_;}

	int getFrameWidth() { return frameWidth_; }
	int getFrameHeight() { return frameHeight_; }

	AnimInfo* getAnimInfoById(ANIM_STATE state);
	void calcNextFrame();
	void addAnimInfo(ANIM_STATE state, int length);

	void calcVertexPoints();
};

#endif
