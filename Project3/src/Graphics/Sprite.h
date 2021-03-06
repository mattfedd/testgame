#ifndef SPRITE_H
#define SPRITE_H

#include "Includes.h"
#include "SpriteSheet.h"

struct AnimInfo
{
	ANIM_STATE id;
	int length;
	int startX;
	int startY;
	bool repeat;
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
	
	bool animating;
	int frame;

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
	Sprite() : width_(0), height_(0), sheet_(NULL) {}
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

	void setAnimating(bool val) {animating = val;}
	bool isAnimating() {return animating;}

	void setAnimState(ANIM_STATE new_state);
	ANIM_STATE getAnimState() {return animState_;}

	int getFrameWidth() { return frameWidth_; }
	void setFrameWidth(int f) { frameWidth_ = f;}
	int getFrameHeight() { return frameHeight_; }
	void setFrameHeight(int f) { frameHeight_ = f;}

	void setFrame(unsigned int val) 
	{
		frame = val;
	}

	AnimInfo* getAnimInfoById(ANIM_STATE state);
	void calcNextFrame();
	void addAnimInfo(ANIM_STATE state, int length, bool repeats = true);

	void calcVertexPoints();
};

#endif
