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
	int frameWidth;
	int frameHeight;
	AnimInfo* next;
};

class Sprite
{
private:
	GLfloat vertexPoints_[12];
	GLfloat texturePoints_[12];
	
	SpriteSheet* sheet_;

	void setVertexPoints(GLfloat* source);
	void setTexturePoints(GLfloat* source);

protected:
	int numAnimations_;
	int width_;
	int height_;
	int sheetWidth_;
	int sheetHeight_;
	int counter_;
	int frameNum_;
	int totalFrames_;

	ANIM_STATE animState_;
	AnimInfo* spriteInfo_;

public:
	//we need width and height for the general vertex points
	//spritesheet for the texture reference
	Sprite(int width, int height, SpriteSheet* ss);
	~Sprite(void);

	GLfloat* getVertexPoints();
	GLfloat* getTexturePoints();

	void setAnimState(ANIM_STATE new_state);

	void setSpriteSheet(SpriteSheet* tex);
	SpriteSheet* getSpriteSheet();

	AnimInfo* getAnimInfoById(ANIM_STATE state);
	void calcNextFrame();
	void addAnimInfo(ANIM_STATE state, int length);
};

#endif
