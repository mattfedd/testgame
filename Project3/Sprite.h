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
	ANIM_STATE animState_;
	SpriteSheet* sheet_;
	//Animation* anim_;

	void setVertexPoints(GLfloat* source);
	void setTexturePoints(GLfloat* source);

public:
	//we need width and height for the general vertex points
	//spritesheet for the texture reference
	Sprite(int width, int height, SpriteSheet* ss);
	~Sprite(void);

	GLfloat* getVertexPoints();
	GLfloat* getTexturePoints();

	void setAnimState(int new_state);

	void setSpriteSheet(SpriteSheet* tex);
	SpriteSheet* getSpriteSheet();
};

#endif
